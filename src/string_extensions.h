/*
  kpack is a KolibriOS-NG archiver, which uses liblzma
  Copyright (C) 2024  Leonid Gribanov
  
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef KPACK_STRING_EXTENSIONS
#define KPACK_STRING_EXTENSIONS

/* This function clone string using malloc() */
/* so free() needed. It returns NULL if malloc() error */
char *kpack_clonestr(const char *);

#endif /* KPACK_STRING_EXTENSIONS */
