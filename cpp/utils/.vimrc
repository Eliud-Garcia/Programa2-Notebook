vim ~/.vimrc


filetype indent on
inoremap {<CR> {<CR><BR>}<Esc>0
inoremap ( ()<Left>
inoremap [ []<Left>
inoremap < <><Left>


syntax on
set exrc
set clipboard=unnamed
set mouse=a
set tabstop=3
set shiftwidth=3
set softtabstop=3
set expandtab

set smarttab
set autoindent
set cindent

set showcmd
set encoding=utf8
set number
set autowrite
set autoread

set nowrap


autocmd filetype cpp nnoremap <F9> :w <bar> !g++ -std=c++11 -Wall -Wextra -O2 -DLOCAL % -o %:r && ./%:r<CR>
autocmd filetype cpp nnoremap <F10> :!%:r<CR>
autocmd filetype cpp nnoremap <C-C> :s/^\(\s*\)/\1\/\/<CR> :s/^\(\s*\)\/\/\/\//\1<CR> $

