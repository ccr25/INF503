//
// Created by Chandler Roe on 11/27/17.
//

#ifndef METAGENOMICSPROJECT_READINGREADS_H
#define METAGENOMICSPROJECT_READINGREADS_H

struct readNode;
readNode * CreateReadNode();
int retrieveNumberOfLines ();
readNode ** populateReadsFileArray( readNode ** readsFile, int kmerSize, int readLength);

#endif //METAGENOMICSPROJECT_READINGREADS_H
