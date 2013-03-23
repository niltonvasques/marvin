/*This file is part of Marvin OS project.
* 
*Marvin OS is free software: you can redistribute it and/or modify
*it under the terms of the GNU General Public License as published by
*the Free Software Foundation, either version 3 of the License, or
*(at your option) any later version.
*
*Marvin OS is distributed in the hope that it will be useful,
*but WITHOUT ANY WARRANTY; without even the implied warranty of
*MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*GNU General Public License for more details.
*
*You should have received a copy of the GNU General Public License
*along with Marvin OS.  If not, see <http://www.gnu.org/licenses/>.
*
*	Description: Kernel Main
*	Author: Nilton Vasques
*	Date: 21 - 03 - 2013
*/

void kmain(){
      // Create a pointer to a char , and point it to the first text cell of
      // video memory ( i . e . the top - left of the screen )
      char *video_memory = (char*) 0xb8000;
      // At the address pointed to by video_memory , store the character ’X ’
      // ( i . e . display ’X ’ in the top - left of the screen ).
      *video_memory = 'X';
}


