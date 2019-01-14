/*
Copyright ESIEE (2009) 

m.couprie@esiee.fr

This software is an image processing library whose purpose is to be
used primarily for research and teaching.

This software is governed by the CeCILL  license under French law and
abiding by the rules of distribution of free software. You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL license and that you accept its terms.
*/
/* \file squelval.c

\brief valuated skeleton of a binary image

<B>Usage:</B> squelval in.pgm dist.pgm connex [inhibit] out.pgm

<B>Description:</B>
Valuated skeleton (ref. CB03) of a binary image.
Requires a precomputed distance map \b dist.pgm .
If the parameter \b inhibit (an integer) is given and is different from -1,
then the points which correspond to this distance value will be left unchanged. 

<B>Types supported:</B> byte 2d, byte 3d

<B>Category:</B> topo
\ingroup  topo

\warning EXPERIMENTAL! DO NOT USE
\author Michel Couprie
*/
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <stdlib.h>
#include <mccodimage.h>
#include <mcimage.h>
#include <lsquelval.h>

/* =============================================================== */
int main(int argc, char **argv)
/* =============================================================== */
{
  struct xvimage * image;
  struct xvimage * dist;
  int32_t connex;
  int32_t inhibit;

  if ((argc != 5) && (argc != 6))
  {
    fprintf(stderr, "usage: %s in.pgm dist.pgm connex [inhibit] out.pgm\n", 
                    argv[0]);
    exit(1);
  }

  image = readimage(argv[1]);
  if (image == NULL)
  {
    fprintf(stderr, "%s: readimage failed\n", argv[0]);
    exit(1);
  }

  dist = readimage(argv[2]);
  if (dist == NULL)
  {
    fprintf(stderr, "%s: readimage failed\n", argv[0]);
    exit(1);
  }

  connex = atoi(argv[3]);
  if (argc == 6) inhibit = atoi(argv[4]); else inhibit = -1;

  if (depth(image) == 1)
  {
    if (! lsquelval(image, dist, connex, inhibit))
/*
    niv = allocimage(NULL, rowsize(image) * colsize(image), 1, 1, VFF_TYP_1_BYTE);
    gra = readimage("_g");
    if (! lsquelsmoothval(image, dist, niv, gra, connex, inhibit, 5))
*/
    {
      fprintf(stderr, "squelval: lsquelval failed\n");
      exit(1);
    }
  }
  else
  {
    if (! lsquelval3d(image, dist, connex, inhibit))
    {
      fprintf(stderr, "squelval: lsquelval3d failed\n");
      exit(1);
    }
  }

  writeimage(dist, argv[argc-1]);
  freeimage(image);
  freeimage(dist);

  return 0;
} /* main */