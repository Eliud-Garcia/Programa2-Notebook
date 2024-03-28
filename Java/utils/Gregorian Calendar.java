
/*agregando n minutos a un tiempo dado
* https://codeforces.com/contest/622/problem/B
*/
public static void main(String[] args) throws IOException {
    String time = next();
    int n = nextInt();
    String hour = time.substring(0, time.indexOf(":"));
    String minute = time.substring(time.indexOf(":") + 1, time.length());
    int h = Integer.parseInt(hour);
    int m = Integer.parseInt(minute);
    GregorianCalendar calendar = new GregorianCalendar(2023, 7, 27, h, m);
    calendar.add(calendar.MINUTE, n);
    int H = calendar.get(calendar.HOUR_OF_DAY);
    int M = calendar.get(calendar.MINUTE);
    
    sa.printf("%0,2d:%0,2d\n", H, M);
    sa.close();
}
/* saber cuando es el dia del siguiente aniversario en n años
* https://codeforces.com/gym/101845/problem/H
*/
public static void main(String[] args) throws IOException {
    int n = nextInt();
    String day[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
    GregorianCalendar c = new GregorianCalendar(1867, 8, 22);
    c.setFirstDayOfWeek(c.MONDAY);
    c.add(c.YEAR, n);
    sa.println(day[c.get(c.DAY_OF_WEEK) - 1]);
    sa.close();
}