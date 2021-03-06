/*
 *  BEAGLE Puppy
 *  Copyright (C) 2001-2004 by Christian Gagne and Marc Parizeau
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  Contact:
 *  Laboratoire de Vision et Systemes Numeriques
 *  Departement de genie electrique et de genie informatique
 *  Universite Laval, Quebec, Canada, G1V 4J7
 *  http://vision.gel.ulaval.ca
 *
 */

/*!
 *  \file   src/Tree.cpp
 *  \brief  Implementation of GP Tree methods.
 *  \author Christian Gagne
 *  \author Marc Parizeau
 *  $Revision: 1.3 $
 *  $Date: 2004/02/11 19:49:23 $
 */

#include "PrimitiveHandle.hpp"
#include "Primitive.hpp"
#include "PrimitiveInline.hpp"
#include "Randomizer.hpp"
#include "Context.hpp"
#include "Tree.hpp"
#include "TokenT.hpp"
#include <QDebug>

/*!
 *  \brief Construct a new tree, with given fitness and validity flag.
 *  \param inFitness Fitness value of the GP tree.
 *  \param inValid Validity of the fitness value.
 */
Puppy::Tree::Tree(float inFitness, bool inValid) :
  mFitness(inFitness),
  mValid(inValid)
{ }


/*!
 *  \brief Return tree depth at given index.
 *  \param inIndex Index of sub-tree root to get the depth from.
 *  \return Sub-tree depth.
 */
unsigned int Puppy::Tree::getDepth(unsigned int inIndex) const
{
  assert(inIndex < size());
  unsigned int lNbArgs = (*this)[inIndex].mPrimitive->getNumberArguments();
  unsigned int lDepth = 1;
  unsigned int j = inIndex + 1;
  for(unsigned int i=0; i<lNbArgs; ++i) {
    unsigned int lChildDepth = getDepth(j) + 1;
    if(lChildDepth > lDepth) lDepth = lChildDepth;
    j += (*this)[j].mSubTreeSize;
  }
  return lDepth;
}


/*!
 *  \brief Interpret the GP tree.
 *  \param outResult Datum containing the result of the interpretation.
 *  \param ioContext Evolutionary context.
 */
void Puppy::Tree::interpret(void* outResult, Puppy::Context& ioContext)
{
  assert(size() > 0);
  ioContext.mTree = this;
  ioContext.mCallStack.push_back(0);
  front().mPrimitive->execute(outResult, ioContext);
  ioContext.mCallStack.pop_back();
}


/*!
 *  \brief Set call stack to include the correctly refer to a given node.
 *  \param inIndex Node index to which call stack must be set.
 *  \param outCallStack Result of call stack setting.
 */
void Puppy::Tree::setStackToNode(unsigned int inIndex,
                                 std::vector<unsigned int>& outCallStack) const
{
  assert(inIndex < size());
  outCallStack.resize(0);
  unsigned int i = 0;
  outCallStack.push_back(i);
  while(i < inIndex) {
    unsigned int lNbArgs=(*this)[i].mPrimitive->getNumberArguments();
    unsigned int lChildIndex = i + 1;
    for(unsigned int j=0; j<lNbArgs; ++j) {
      if((lChildIndex+(*this)[lChildIndex].mSubTreeSize) > inIndex) break;
      lChildIndex += (*this)[lChildIndex].mSubTreeSize;
    }
    assert(lChildIndex < size());
    i = lChildIndex;
    outCallStack.push_back(i);
  }
  assert(i == inIndex);
}


/*!
 *  \brief Write GP tree at given index as a s-expression into a C++ output stream.
 *  \param ioOS C++ output stream to write tree into.
 *  \param inIndex Actual node index in tree.
 */
void Puppy::Tree::write(std::ostream& ioOS, unsigned int inIndex) const
{
  assert(inIndex < size());
  unsigned int lNbArgs = (*this)[inIndex].mPrimitive->getNumberArguments();
  if(lNbArgs > 0) ioOS << '(';
  ioOS << (*this)[inIndex].mPrimitive->getName();
  unsigned int j = inIndex + 1;
  for(unsigned int i=0; i<lNbArgs; ++i) {
    ioOS << ' ';
    write(ioOS, j);
    j += (*this)[j].mSubTreeSize;
  }
  if(lNbArgs > 0) ioOS << ')';
}

void Puppy::Tree::write_qstring(QString& ioOS, unsigned int inIndex) const
{
  assert(inIndex < size());
  unsigned int lNbArgs = (*this)[inIndex].mPrimitive->getNumberArguments();
  if(lNbArgs > 0) ioOS.append("(");
  ioOS.append(QString::fromStdString((*this)[inIndex].mPrimitive->getName()));
  unsigned int j = inIndex + 1;
  for(unsigned int i=0; i<lNbArgs; ++i) {
    ioOS.append(" ");
    write_qstring(ioOS, j);
    j += (*this)[j].mSubTreeSize;
  }
  if(lNbArgs > 0) ioOS.append(")");
}

void Puppy::Tree::write_qstring_infix(QString& ioOS, unsigned int inIndex) const
{

  assert(inIndex < size());
  unsigned int lNbArgs = (*this)[inIndex].mPrimitive->getNumberArguments();
  if(lNbArgs > 0) {
    ioOS.append("(");
  }
  if(lNbArgs == 0) ioOS.append(QString::fromStdString((*this)[inIndex].mPrimitive->getName()));

  unsigned int j = inIndex + 1;
  bool unarity = false;
  for(unsigned int i=0;i<lNbArgs;++i) {
    //output.append(" ");
    if((i==0) && (lNbArgs==1)) {
      ioOS.append(QString::fromStdString((*this)[inIndex].mPrimitive->getName()));
      if((*this)[inIndex+1].mPrimitive->getNumberArguments()==0) {
        ioOS.append("(");
        unarity = true;
      }
    }
    if((i==1) && (lNbArgs==2)) ioOS.append(QString::fromStdString((*this)[inIndex].mPrimitive->getName()));
    write_qstring_infix(ioOS,j);
    j += (*this)[j].mSubTreeSize;
  }

  if(unarity) {
    ioOS.append(")");
    unarity = false;
  }
  if(lNbArgs > 0) ioOS.append(")");
}

void Puppy::Tree::write_qstring_latex(QString& ioOS, unsigned int inIndex) const
{
  assert(inIndex < size());
  unsigned int lNbArgs = (*this)[inIndex].mPrimitive->getNumberArguments();
  if(lNbArgs > 0) {
    ioOS.append("(");
  }
  if(lNbArgs == 0) {
    QString temp = QString::fromStdString((*this)[inIndex].mPrimitive->getName());
    if(temp.at(0)=='X') {
      temp.insert(1,"_{");
      temp.append("}");
      ioOS.append(temp);
    } else ioOS.append(QString::fromStdString((*this)[inIndex].mPrimitive->getName()));
  }
  if((*this)[inIndex].mPrimitive->getName()=="/") ioOS.append("\\frac{");

  unsigned int j = inIndex + 1;
  bool unarity = false;
  for(unsigned int i=0;i<lNbArgs;++i) {

    if((i==0) && (lNbArgs==1)) {
      ioOS.append(QString::fromStdString((*this)[inIndex].mPrimitive->getName()));
      if((*this)[inIndex+1].mPrimitive->getNumberArguments()==0) {
        ioOS.append("(");
        unarity = true;
      }
    }
    if((i==1) && (lNbArgs==2)) {
      if((*this)[inIndex].mPrimitive->getName()=="/") ioOS.append("}{");
      else ioOS.append(QString::fromStdString((*this)[inIndex].mPrimitive->getName()));
    }
    write_qstring_latex(ioOS,j);
    j += (*this)[j].mSubTreeSize;
  }

  if(unarity) {
    ioOS.append(")");
    unarity = false;
  }
  if(lNbArgs > 0) {
    if((*this)[inIndex].mPrimitive->getName()=="/") ioOS.append("}");
    else ioOS.append(")");
  }
}

void Puppy::Tree::tree2infix(QString& ioOS, std::vector<unsigned int> depthV, int index) const
{
  QVector<QString> args;
  ioOS.clear();
  ioOS.append(QString::fromStdString((*this)[index].mPrimitive->getName()));
  args.clear();
  unsigned int lNbArgs = (*this)[index].mPrimitive->getNumberArguments();
  int counter = 0;
  for(unsigned int i=0;i<lNbArgs;i++) {
    int currentdepth = depthV.at(index);
    //find its childrens
    do {
      if(depthV.at(counter+index) == (currentdepth+1)) {
         counter += 1;
         break;
      }
      counter += 1;
    }while((index + counter)<size());
    QString children = QString::fromStdString((*this)[index+counter-1].mPrimitive->getName());
    args.push_back(children);
    QString text = args.at(i);
    index += 1;
    tree2infix(text,depthV,index);
  }

  if(!args.isEmpty()) {
    unsigned int lNbArgs = (*this)[index].mPrimitive->getNumberArguments();
    if(lNbArgs==2) {
      ioOS.append("(" + args.at(0) + ioOS + args.at(1) + ")");
    }
  }
}

void Puppy::Tree::extractparentsdepth(std::vector<unsigned int>& depthV, int index, int depth) const
{
  unsigned int j = index + 1;
  unsigned int lNbArgs = (*this)[index].mPrimitive->getNumberArguments();
  for(unsigned int i = 0;i<lNbArgs;i++) {
    extractparentsdepth(depthV,j,depth+1);
    j += (*this)[j].mSubTreeSize;
  }
  if((*this)[index].mSubTreeSize>1) {
    int counter = 0;
    unsigned int lNbArgs = (*this)[index].mPrimitive->getNumberArguments();
    for(unsigned int k=0;k<lNbArgs;k++) {
      do // Search for childrens
      {
        if(depthV.at(index + counter) == (depth + 1)) {
          counter += 1;
          break;
        }
        counter += 1;
      }while((index + counter) < size());
    }
    depthV.at(index) = depth;
  }
}

void Puppy::Tree::extractleavesdepth(std::vector<unsigned int> &depthV, int index, int depth) const
{
  if((*this)[index].mSubTreeSize == 1) {
    depthV.at(index) = depth;
  }
  unsigned int j = index + 1;
  unsigned int lNbArgs = (*this)[index].mPrimitive->getNumberArguments();
  for(unsigned int i = 0;i<lNbArgs;i++) {
    extractleavesdepth(depthV,j,depth+1);
    j += (*this)[j].mSubTreeSize;
  }
}
