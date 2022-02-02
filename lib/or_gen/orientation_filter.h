//
// Copyright (c) 2002 The Regents of the University of California.
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//   1. Redistributions of source code must retain the above copyright
//      notice, this list of conditions, and the following disclaimer.
//   2. Redistributions in binary form must reproduce the above
//      copyright notice, this list of conditions, and the following
//      disclaimer in the documentation and/or other materials provided
//      with the distribution.
//   3. Redistributions must acknowledge that this software was
//      originally developed by the UCSF Computer Graphics Laboratory
//      under support by the NIH National Center for Research Resources,
//      grant P41-RR01081.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
// OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
// BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
// OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef _ORIENTATION_FILTER_H
#define _ORIENTATION_FILTER_H
#include <vect_3d.h>
#include <biopolymer.h>
#include <pair_alignment.h>
#include <dynNW.h>

//OrientationFilter
//contains a function "GoodOrientation()"
//that, in O(mn) time, calculates whether any
//"good" alignments can be found between two
//structures when the orientation between them is fixed.
//A "good" alignment is one which contains at least 
//"set_min_num_matches" pairs of residues that are all
//within "set_max_phys_distance" of eachother.
//
//This function can be used to filter out the "bad" orientations
//that are generated by the OrientationGenerator class (see "or_gen.h")

namespace minrms
{

class OrientationFilter
{
  Real                 gap_penalty;
  Real                 max_phys_distance;
  int                  min_num_matches;
  DynNW                dyn_nw;
  PairwiseAlignment    solution;

public:
  OrientationFilter(
        Real set_max_phys_distance, //maximum(RMS)distance between residues
                                    //(a parameter for filtering)
        int  set_min_num_matches,   //minimum number of matches in alignment
                                    //(a parameter for filtering)
        int  numRes1,  //number of residues in the first structure
        int  numRes2); //number of residues in the second structure
                       //(This needs to be known in advance in order to
                       // know how large to make the Needleman&Wunsch style
                       // dynamic programing table that will be used later.)

  //GoodOrientation()
  //takes the two candidate structures rotated and translated
  //in advance, and predicts whether, at this orientation,
  //an alignment could be made between these structures
  //containing at least "set_min_num_matches" pairs of residues
  //that are within "set_max_phys_distance" of eachother.
  bool GoodOrientation(Biopolymer const& m1_rotated,
                       Biopolymer const& m2_rotated);
}; //class OrientationFilter

} //namespace minrms


#endif // #ifndef _ORIENTATION_FILTER_H