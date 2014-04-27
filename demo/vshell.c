/*
Copyright (C) 2009 Bryan Christ

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

/*
This library is based on ROTE written by Bruno Takahashi C. de Oliveira
*/

#include <ncurses.h>
#include <stdio.h>
#include <signal.h>
#include <locale.h>

#include <vterm.h>

int main()
{
   setlocale(LC_ALL,"");

   initscr();
   noecho();
   start_color();
   raw();
   nodelay(stdscr, TRUE);
   keypad(stdscr, TRUE);

   /* create a window with a frame */
   WINDOW *term_win = newwin(25,80,1,4);

   vterm_t *vterm=vterm_create(80,25,VTERM_FLAG_VT100);
   vterm_set_colors(vterm, COLOR_BLACK, COLOR_WHITE);
   vterm_wnd_set(vterm,term_win);

   int i, j;
   for (i = 0; i < 25; i++) for (j = 0; j < 80; j++) addch(' ');

   int ch = '\0';
   ssize_t bytes;
   while (ch != 'D')
   {
      bytes=vterm_read_pipe(vterm);
      if(bytes > 0)
      {
         vterm_wnd_update(vterm);
         touchwin(term_win);
         wrefresh(term_win);
         refresh();
      }

      if(bytes==-1) break;

      ch = getch();
      if (ch != ERR) vterm_write_pipe(vterm,ch);
   }

   vterm_destroy(vterm);

   endwin();
   return 0;
}


