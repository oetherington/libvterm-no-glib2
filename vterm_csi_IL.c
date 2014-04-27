/*
 * Modifed to remove glib2.0 dependency by Ollie Etherington (C) Copyright 2014
 *
 * libvterm Copyright (C) 2009 Bryan Christ
 * libvterm is based on ROTE written by Bruno Takahashi C. de Oliveira
 *
 * As per previous releases, this program is available under the GNU GPL v2
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <string.h>

#include "vterm.h"
#include "vterm_private.h"
#include "vterm_csi.h"

/* Interpret an 'insert line' sequence (IL) */
void interpret_csi_IL(vterm_t *vterm,int param[],int pcount)
{
   int i, j;
   int n=1;

   if(pcount && param[0] > 0) n=param[0];

   for(i=vterm->scroll_max;i >= vterm->crow+n;i--)
   {
      memcpy(vterm->cells[i],vterm->cells[i - n],
         sizeof(vterm_cell_t)*vterm->cols);
   }

   for(i=vterm->crow;i < vterm->crow+n; i++)
   {
      if(i>vterm->scroll_max) break;

      for(j=0;j < vterm->cols; j++)
      {
         vterm->cells[i][j].ch = 0x20;
         vterm->cells[i][j].attr=vterm->curattr;
      }
   }

   return;
}
