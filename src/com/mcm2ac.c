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
/* 
  Michel Couprie  -  Mars 2002
*/

#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <mccodimage.h>
#include <mcimage.h>
#include <mcrbtp.h>
#include <mcmesh.h>
#include <mciomesh.h>

/* =============================================================== */
int main(int argc, char **argv) 
/* =============================================================== */
{
  FILE *filein = NULL;
  FILE *fileout = NULL;
  meshbox MB0; 

  if (argc != 3)
  {
    fprintf(stderr, "usage: %s in.mcm out.mcm\n", argv[0]);
    exit(0);
  }

  filein = fopen(argv[1],"r");
  LoadMeshMCM(filein);
  fclose(filein);
  BoundingBoxMesh(&MB0);
  fileout = fopen(argv[2],"w");
  genheaderAC(fileout, MB0, 1.0, 1.0, 1.0, (char *)"obj");
  SaveMeshAC(fileout);
  genfooterAC(fileout);
  fclose(fileout);
  TermineMesh();
  return 0;
} /* main */