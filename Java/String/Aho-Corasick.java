import java.io.Serializable;
import java.util.*;
import java.util.function.BiPredicate;



/*
     * Dado un listado de palabras, busca eficientemente
     * si estan un texto, indicando idx de inicio y fin
     */

    static class Emit implements Serializable {
        private static final long serialVersionUID = -8879895979621579720L;
        /** The beginning index and ending, inclusive. */
        private final int begin;
        private final int end;
        private final String keyword;

        public Emit(int begin, int end, String keyword) {
            this.begin = begin;
            this.end = end;
            this.keyword = keyword;
        }

        public int getBegin() {
            return begin;
        }

        public int getEnd() {
            return end;
        }

        public int getLength() {
            return end - begin;
        }

        public String getKeyword() {
            return keyword;
        }

        public boolean overlaps(Emit o) {
            return this.begin < o.end && this.end > o.begin;
        }

        public boolean contains(Emit o) {
            return this.begin <= o.begin && this.end >= o.end;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o)
                return true;
            if (!(o instanceof Emit))
                return false;
            Emit that = (Emit) o;
            return this.begin == that.begin
                    && this.end == that.end
                    && Objects.equals(this.keyword, that.keyword);
        }

        @Override
        public int hashCode() {
            return Objects.hash(begin, end, keyword);
        }

        @Override
        public String toString() {
            return keyword + " = (" + begin + ":" + end + ")";
        }
    }

    static class Emits extends ArrayList<Emit> {
        private static final long serialVersionUID = -9117361135147927914L;
        private final CharSequence source;

        public Emits(CharSequence source) {
            this.source = source;
        }

        private Emits(Emits emits) {
            super(emits);
            this.source = emits.source;
        }

        public CharSequence getSource() {
            return source;
        }

        public List<Token> tokenize() {
            Emits emits = this.copy();
            emits.removeContains();
            String source = emits.getSource().toString();
            List<Token> tokens = new ArrayList<>(emits.size() * 2 + 1);
            if (emits.isEmpty()) {
                tokens.add(new Token(source, null));
                return tokens;
            }
            int index = 0;
            for (Emit emit : emits) {
                if (index < emit.getBegin()) {
                    tokens.add(new Token(source.substring(index, emit.getBegin()), null));
                }
                tokens.add(new Token(source.substring(emit.getBegin(), emit.getEnd()), emit));
                index = emit.getEnd();
            }
            Emit last = emits.get(emits.size() - 1);
            if (last.getEnd() < source.length()) {
                tokens.add(new Token(source.substring(last.getEnd()), null));
            }
            return tokens;
        }

        public String replaceWith(String replacement) {
            Emits emits = this.copy();
            emits.removeContains();
            String source = emits.getSource().toString();
            if (emits.isEmpty()) {
                return source;
            }
            int index = 0;
            StringBuilder sb = new StringBuilder();
            for (Emit emit : this) {
                if (index < emit.getBegin()) {
                    sb.append(source, index, emit.getBegin());
                    index = emit.getBegin();
                }
                sb.append(mask(replacement, index, emit.getEnd()));
                index = emit.getEnd();
            }
            Emit last = emits.get(emits.size() - 1);
            if (last.getEnd() < source.length()) {
                sb.append(source, last.getEnd(), source.length());
            }
            return sb.toString();
        }

        public void removeOverlaps() {
            removeIf(Emit::overlaps);
        }

        public void removeContains() {
            removeIf(Emit::contains);
        }

        private void removeIf(BiPredicate<Emit, Emit> predicate) {
            if (this.size() <= 1) {
                return;
            }
            this.sort();
            Iterator<Emit> iterator = this.iterator();
            Emit emit = iterator.next();
            while (iterator.hasNext()) {
                Emit next = iterator.next();
                if (predicate.test(emit, next)) {
                    iterator.remove();
                } else {
                    emit = next;
                }
            }
        }

        private void sort() {
            this.sort((a, b) -> {
                if (a.getBegin() != b.getBegin()) {
                    return Integer.compare(a.getBegin(), b.getBegin());
                } else {
                    return Integer.compare(b.getEnd(), a.getEnd());
                }
            });
        }

        private String mask(String replacement, int begin, int end) {
            int count = end - begin;
            int len = replacement != null ? replacement.length() : 0;
            if (len == 0) {
                return repeat("*", count);
            } else if (len == 1) {
                return repeat(replacement, count);
            } else {
                char[] chars = new char[count];
                for (int i = 0; i < count; i++) {
                    chars[i] = replacement.charAt((i + begin) % len);
                }
                return new String(chars);
            }
        }

        private String repeat(String s, int count) {
            if (count < 0) {
                throw new IllegalArgumentException("count is negative: " + count);
            }
            if (count == 1) {
                return s;
            }
            final int len = s.length();
            if (len == 0 || count == 0) {
                return "";
            }
            if (Integer.MAX_VALUE / count < len) {
                throw new OutOfMemoryError("Required length exceeds implementation limit");
            }
            if (len == 1) {
                final char[] single = new char[count];
                Arrays.fill(single, s.charAt(0));
                return new String(single);
            }
            final int limit = len * count;
            final char[] multiple = new char[limit];
            System.arraycopy(s.toCharArray(), 0, multiple, 0, len);
            int copied = len;
            for (; copied < limit - copied; copied <<= 1) {
                System.arraycopy(multiple, 0, multiple, copied, copied);
            }
            System.arraycopy(multiple, 0, multiple, copied, limit - copied);
            return new String(multiple);
        }

        private Emits copy() {
            return new Emits(this);
        }
    }

    static class State implements Serializable {
        private static final long serialVersionUID = -6350361756888572415L;
        private final int depth;
        private Map<Character, State> success;
        private State failure;
        private TreeSet<String> keywords;

        public State(int depth) {
            this.depth = depth;
        }

        public State nextState(char c) {
            return nextState(c, false);
        }

        public State nextState(char c, boolean ignoreCase) {
            State next = getState(c, ignoreCase);
            if (next != null) {
                return next;
            } else if (depth == 0) {
                return this;
            }
            return null;
        }

        public State getState(char c) {
            return success != null ? success.get(c) : null;
        }

        public State getState(char c, boolean ignoreCase) {
            if (success == null) {
                return null;
            }
            State state = success.get(c);
            if (state != null) {
                return state;
            }
            if (ignoreCase) {
                char cc;
                if (Character.isLowerCase(c)) {
                    cc = Character.toUpperCase(c);
                } else if (Character.isUpperCase(c)) {
                    cc = Character.toLowerCase(c);
                } else {
                    cc = c;
                }
                if (c != cc) {
                    return success.get(cc);
                }
            }
            return null;
        }

        public State addState(CharSequence cs) {
            State state = this;
            for (int i = 0; i < cs.length(); i++) {
                state = state.addState(cs.charAt(i));
            }
            return state;
        }

        public State addState(char c) {
            if (success == null) {
                success = new HashMap<>();
            }
            State state = success.get(c);
            if (state == null) {
                state = new State(depth + 1);
                success.put(c, state);
            }
            return state;
        }

        public void addKeyword(String keyword) {
            if (this.keywords == null) {
                this.keywords = new TreeSet<>();
            }
            this.keywords.add(keyword);
        }

        public void addKeywords(Collection<String> keywords) {
            if (this.keywords == null) {
                this.keywords = new TreeSet<>();
            }
            this.keywords.addAll(keywords);
        }

        public Set<String> getKeywords() {
            return keywords != null ? keywords : Collections.emptySet();
        }

        public String getFirstKeyword() {
            return keywords != null && keywords.size() > 0 ? keywords.first() : null;
        }

        public State getFailure() {
            return failure;
        }

        public void setFailure(State failure) {
            this.failure = failure;
        }

        public Map<Character, State> getSuccess() {
            return success != null ? success : Collections.emptyMap();
        }

        public int getDepth() {
            return depth;
        }

        public boolean isRoot() {
            return depth == 0;
        }
    }

    static class Token implements Serializable {
        private static final long serialVersionUID = -7918430275428907853L;
        private final String fragment;
        private final Emit emit;

        public Token(String fragment, Emit emit) {
            this.fragment = fragment;
            this.emit = emit;
        }

        public String getFragment() {
            return this.fragment;
        }

        public Emit getEmit() {
            return emit;
        }

        public boolean isMatch() {
            return emit != null;
        }

        @Override
        public String toString() {
            if (emit == null) {
                return fragment;
            } else {
                return fragment + "(" + emit + ")";
            }
        }
    }

    static class Aho_Corasick implements Serializable {
        private static final long serialVersionUID = 7464998650081881647L;
        private final State root;

        public Aho_Corasick() {
            this.root = new State(0);
        }

        public Aho_Corasick(Set<String> keywords) {
            this.root = new State(0);
            this.addKeywords(keywords);
        }

        public Aho_Corasick(String... keywords) {
            this.root = new State(0);
            this.addKeywords(keywords);
        }

        public Aho_Corasick addKeywords(Set<String> keywords) {
            for (String keyword : keywords) {
                if (keyword != null && !keyword.isEmpty()) {
                    root.addState(keyword).addKeyword(keyword);
                }
            }
            Queue<State> states = new LinkedList<>();
            root.getSuccess().forEach((ignored, state) -> {
                state.setFailure(root);
                states.add(state);
            });
            while (!states.isEmpty()) {
                State state = states.poll();
                state.getSuccess().forEach((c, next) -> {
                    State f = state.getFailure();
                    State fn = f.nextState(c);
                    while (fn == null) {
                        f = f.getFailure();
                        fn = f.nextState(c);
                    }
                    next.setFailure(fn);
                    next.addKeywords(fn.getKeywords());
                    states.add(next);
                });
            }
            return this;
        }

        public Aho_Corasick addKeywords(String... keywords) {
            if (keywords == null || keywords.length == 0) {
                return this;
            }
            Set<String> keywordSet = new HashSet<>();
            Collections.addAll(keywordSet, keywords);
            return addKeywords(keywordSet);
        }

        public Emits findAll(CharSequence text, boolean ignoreCase) {
            Emits emits = new Emits(text);
            State state = root;
            for (int i = 0, len = text.length(); i < len; i++) {
                state = nextState(state, text.charAt(i), ignoreCase);
                for (String keyword : state.getKeywords()) {
                    // retorna el idx del inicio y fin donde esta la keyword
                    // emits.add(new Emit(i - keyword.length() + 1, i + 1 , keyword));
                    emits.add(new Emit(i - keyword.length() + 1, i, keyword));
                }
            }
            return emits;
        }

        public Emits findAll(CharSequence text) {
            return findAll(text, false);
        }

        public Emits findAllIgnoreCase(CharSequence text) {
            return findAll(text, true);
        }

        public Emit findFirst(CharSequence text, boolean ignoreCase) {
            State state = root;
            for (int i = 0, len = text.length(); i < len; i++) {
                state = nextState(state, text.charAt(i), ignoreCase);
                String keyword = state.getFirstKeyword();
                if (keyword != null) {
                    return new Emit(i - keyword.length() + 1, i + 1, keyword);
                }
            }
            return null;
        }

        public Emit findFirst(CharSequence text) {
            return findFirst(text, false);
        }

        public Emit findFirstIgnoreCase(CharSequence text) {
            return findFirst(text, true);
        }

        private State nextState(State state, char c, boolean ignoreCase) {
            State next = state.nextState(c, ignoreCase);
            while (next == null) {
                state = state.getFailure();
                next = state.nextState(c, ignoreCase);
            }
            return next;
        }
    }

    public static void main(String[] args) {
        Set<String> words = new HashSet<>();
        words.add("he");
        words.add("rs");
        words.add("his");
        words.add("hers");
        words.add("hol");
        Aho_Corasick t = new Aho_Corasick(words);
        System.out.println(t.findAll("ushershe"));
    }