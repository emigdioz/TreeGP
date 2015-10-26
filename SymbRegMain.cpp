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
 *  \file   SymbRegMain.cpp
 *  \brief  Implementation symbolic regression main routine.
 *  \author Christian Gagne
 *  \author Marc Parizeau
 *  $Revision: 1.5 $
 *  $Date: 2004/02/11 18:38:12 $
 */

/*!
 *  \defgroup SymbReg Symbolic Regression Example
 *  \brief Symbolic regression (symbreg): A simple GP example with BEAGLE Puppy.
 *
 *  \par Objective
 *  Find a function of one independent variable and one dependent variable, in
 *  symbolic form, that fits a given sample of 20 \f$(x_i,y_i)\f$ data points,
 *  where the target function is the quadratic polynomial \f$x^4 + x^3 + x^2 + x\f$.
 *
 *  \par Terminal set
 *  - X (the independent variable)
 *  - Ephemeral constants randomly generated in [-1,1]
 *
 *  \par Function set
 *  - +
 *  - -
 *  - *
 *  - /     (protected division)
 *
 *  \par Fitness cases
 *  The given sample of 20 data points \f$(x_i,y_i)\f$, randomly chosen within
 *  interval [-1,1].
 *
 *  \par Fitness
 *  \f$\frac{1.}{1.+RMSE}\f$ where RMSE is the Root Mean Square Error on the
 *  fitness cases.
 *
 *  \par Stopping criteria
 *  When the evolution reaches the maximum number of generations.
 *
 *  \par Reference
 *  John R. Koza, "Genetic Programming: On the Programming of Computers by Means
 *  of Natural Selection", MIT Press, 1992, pages 162-169.
 *
 */
 
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <QVector>
#include <QString>
#include <sstream>
#include <QDebug>
#include <algorithm>

#include "Puppy.hpp"
#include "SymbRegPrimits.hpp"
#include "mainwindow.h"
#include "optionsdialog.h"
#include "worker.h"
#include "matrix.h"
#include "infix.h"

#define POP_SIZE_DEFAULT 100
#define NBR_GEN_DEFAULT 100
#define NBR_PART_TOURNAMENT_DEFAULT 10
#define MAX_DEPTH_DEFAULT 17
#define MIN_INIT_DEPTH_DEFAULT 2
#define MAX_INIT_DEPTH_DEFAULT 5
#define INIT_GROW_PROBA_DEFAULT 0.5f
#define CROSSOVER_PROBA_DEFAULT 0.9f
#define CROSSOVER_DISTRIB_PROBA_DEFAULT 0.9f
#define MUT_STD_PROBA_DEFAULT 0.05f
#define MUT_MAX_REGEN_DEPTH_DEFAULT 5
#define MUT_SWAP_PROBA_DEFAULT 0.05f
#define MUT_SWAP_DISTRIB_PROBA_DEFAULT 0.5f
#define SEED_DEFAULT 0


using namespace Puppy;


unsigned int evaluateFitness(std::vector<Tree>& ioPopulation,
                             Context& ioContext,
                             double* inX,
                             double* inF,int cols, int rows);

unsigned int evaluateFitnessTesting(Tree &individual,
                             Context& ioContext,
                             double* inX,
                             double* inF,int cols, int rows);

unsigned int evaluateFitnessTraining(Tree &individual,
                             Context& ioContext,
                             double* inX,
                             double* inF,int cols, int rows);

void passTree(Tree &individual,Worker::TreeStruct& tree);

/*!
 *  \brief Program main routine.
 *  \param argc Number of arguments given on the command-line.
 *  \param argv Command-line arguments.
 *  \ingroup SymbReg
 */
int Worker::start_main(void) {

  // Create parameter variables with default values.
  unsigned int  lPopSize             = POP_SIZE_DEFAULT;
  unsigned int  lNbrGen              = NBR_GEN_DEFAULT;
  unsigned int  lNbrPartTournament   = NBR_PART_TOURNAMENT_DEFAULT;
  unsigned int  lMaxDepth            = MAX_DEPTH_DEFAULT;
  unsigned int  lMinInitDepth        = MIN_INIT_DEPTH_DEFAULT;
  unsigned int  lMaxInitDepth        = MAX_INIT_DEPTH_DEFAULT;
  float         lInitGrowProba       = INIT_GROW_PROBA_DEFAULT;
  float         lCrossoverProba      = CROSSOVER_PROBA_DEFAULT;
  float         lCrossDistribProba   = CROSSOVER_DISTRIB_PROBA_DEFAULT;
  float         lMutStdProba         = MUT_STD_PROBA_DEFAULT;
  unsigned int  lMutMaxRegenDepth    = MUT_MAX_REGEN_DEPTH_DEFAULT;
  float         lMutSwapProba        = MUT_SWAP_PROBA_DEFAULT;
  float         lMutSwapDistribProba = MUT_SWAP_DISTRIB_PROBA_DEFAULT;
  unsigned long lSeed                = SEED_DEFAULT;

  lNbrGen = Worker::ngen;
  lPopSize = Worker::popsize;
  lNbrPartTournament = Worker::tournamentsize;
  lMaxDepth = Worker::maxdepth;
  lMinInitDepth = Worker::mininitdepth;
  lMaxInitDepth = Worker::maxinitdepth;
  lCrossoverProba = Worker::crossoverp;
  lCrossDistribProba = Worker::crossoverdp;
  lMutStdProba = Worker::mutationp;
  lMutMaxRegenDepth = Worker::mutationmaxr;
  lSeed = Worker::randomseed;

  // Display message with parameters used.
  std::cout << "BEAGLE Puppy symbolic regression" << std::endl;

  //textEdit->insertPlainText("Ejemplo\n");
  std::cout << "Copyright 2001-2004 by Christian Gagne and Marc Parizeau" << std::endl;
  std::cout << "Parameters used are:" << std::endl;
  std::cout << " Population size:                           " << lPopSize << std::endl;
  std::cout << " Number of generations:                     " << lNbrGen << std::endl;
  std::cout << " Number participants tournament:            " << lNbrPartTournament << std::endl;
  std::cout << " Maximum tree depth:                        " << lMaxDepth << std::endl;
  std::cout << " Minimum tree initialization depth:         " << lMinInitDepth << std::endl;
  std::cout << " Maximum tree initialization depth:         " << lMaxInitDepth << std::endl;
  std::cout << " Grow-type initialization proba.:           " << lInitGrowProba << std::endl;
  std::cout << " Crossover probability:                     " << lCrossoverProba << std::endl;
  std::cout << " Crossover distribution probability:        " << lCrossDistribProba << std::endl;
  std::cout << " Standard (Koza's) mutation proba.:         " << lMutStdProba << std::endl;
  std::cout << " Standard mutation max. regeneration depth: " << lMutMaxRegenDepth << std::endl;
  std::cout << " Swap point mutation probability:           " << lMutSwapProba << std::endl;
  std::cout << " Swap point mutation distribution proba.:   " << lMutSwapDistribProba << std::endl;
  std::cout << " Random number generator seed value:        " << lSeed << std::endl;
  
  emit Worker::valueChanged(" Population size:                           " + QString::number(lPopSize));
  emit Worker::valueChanged(" Number of generations:                     " + QString::number(lNbrGen));
  emit Worker::valueChanged(" Number participants tournament:            " + QString::number(lNbrPartTournament));
  emit Worker::valueChanged(" Maximum tree depth:                        " + QString::number(lMaxDepth));
  emit Worker::valueChanged(" Minimum tree initialization depth:         " + QString::number(lMinInitDepth));
  emit Worker::valueChanged(" Maximum tree initialization depth:         " + QString::number(lMaxInitDepth));
  emit Worker::valueChanged(" Grow-type initialization proba.:           " + QString::number(lInitGrowProba));
  emit Worker::valueChanged(" Crossover probability:                     " + QString::number(lCrossoverProba));
  emit Worker::valueChanged(" Crossover distribution probability:        " + QString::number(lCrossDistribProba));
  emit Worker::valueChanged(" Standard (Koza's) mutation proba.:         " + QString::number(lMutStdProba));
  emit Worker::valueChanged(" Standard mutation max. regeneration depth: " + QString::number(lMutMaxRegenDepth));
  emit Worker::valueChanged(" Swap point mutation probability:           " + QString::number(lMutSwapProba));
  emit Worker::valueChanged(" Swap point mutation distribution proba.:   " + QString::number(lMutSwapDistribProba));
  emit Worker::valueChanged(" Random number generator seed value:        " + QString::number(lSeed));

  emit Worker::GPstarted("Stop");
  // Create evolution context add primitives used into it.
  std::cout << "Creating evolution context" << std::endl;
  emit Worker::valueChanged("Creating evolution context");
  Context lContext;
  lContext.mRandom.seed(lSeed);
  emit Worker::valueChanged("Function set selected");
  if(Worker::functionselection.at(0)) {
    emit Worker::valueChanged("Add");
    lContext.insert(new Add);
  }
  if(Worker::functionselection.at(1)) {
    emit Worker::valueChanged("Substract");
    lContext.insert(new Subtract);
  }
  if(Worker::functionselection.at(2)) {
    emit Worker::valueChanged("Multiply");
    lContext.insert(new Multiply);
  }
  if(Worker::functionselection.at(3)) {
    emit Worker::valueChanged("Divide");
    lContext.insert(new Divide);
  }
  if(Worker::functionselection.at(4)) {
    emit Worker::valueChanged("Sin");
    lContext.insert(new Sin);
  }
  if(Worker::functionselection.at(5)) {
    emit Worker::valueChanged("Cos");
    lContext.insert(new Cos);
  }
  if(Worker::functionselection.at(6)) {
    emit Worker::valueChanged("Log");
    lContext.insert(new Log);
  }
  if(Worker::functionselection.at(7)) {
    emit Worker::valueChanged("Exp");
    lContext.insert(new Exp);
  }

  // Add terminals
  std::stringstream str;
  for(unsigned int i=0; i<Worker::dataset_cols-1;i++) {
    str<<"X"<<(i+1);
    lContext.insert(new TokenT<double>(str.str(), 0.0));
    str.str(std::string());
  }

  // Prepare data, separating input and output variables
  std::vector<int> index;
  for (unsigned int i=0; i<Worker::dataset_rows; ++i) index.push_back(i);
  // Make random indexing for training,testing partitioning
  std::random_shuffle ( index.begin(), index.end() );
  int *index_int = new int [Worker::dataset_rows];
  std::copy(index.begin(), index.end(), index_int);

  int size_training = (float)Worker::dataset_rows*(float)Worker::trainingP/100;
  double *trainingSet = new double[size_training*Worker::dataset_cols];
  double *testingSet = new double[(Worker::dataset_rows-size_training)*Worker::dataset_cols];
  Worker::subsetData(Worker::dataset,trainingSet,testingSet,Worker::dataset_cols,Worker::dataset_rows,size_training,index_int);

  double *trainingIn = new double [size_training*(Worker::dataset_cols-1)];
  double *trainingOut = new double [size_training];
  double *testingIn = new double [(Worker::dataset_rows-size_training)*(Worker::dataset_cols-1)];
  double *testingOut = new double [(Worker::dataset_rows-size_training)];

  double *inputV = new double [Worker::dataset_rows*(Worker::dataset_cols-1)];
  double *outputV = new double[Worker::dataset_rows];

  for(unsigned int j = 0;j < (Worker::dataset_cols-1);j++) {
      // Training data
      for(unsigned int i = 0;i < size_training;i++) {
          trainingIn[(j*size_training)+i] = trainingSet[(j*size_training)+i];
      }
      // Testing data
      for(unsigned int i = 0;i < (Worker::dataset_rows-size_training);i++) {
          testingIn[(j*(Worker::dataset_rows-size_training))+i] = testingSet[(j*(Worker::dataset_rows-size_training))+i];
      }

  }

  //qDebug()<<"Training";
  for(unsigned int i = 0;i < size_training;i++) {
    trainingOut[i] = trainingSet[((Worker::dataset_cols-1)*size_training)+i];
    //qDebug()<<i<<": "<<trainingOut[i];
  }
  //qDebug()<<"Testing";
  for(unsigned int i = 0;i < (Worker::dataset_rows-size_training);i++) {
    testingOut[i] = testingSet[((Worker::dataset_cols-1)*(Worker::dataset_rows-size_training))+i];
    //qDebug()<<i<<": "<<testingOut[i];
  }
  emit Worker::valueChanged("Training size = " + QString::number(size_training) + " x " + QString::number(Worker::dataset_cols-1));
  emit Worker::valueChanged("Testing size = " + QString::number(Worker::dataset_rows-size_training) + " x " + QString::number(Worker::dataset_cols-1));

  // Initialize population.
  std::vector<Tree> lPopulation(lPopSize);
  std::cout << "Initializing population" << std::endl;
  emit Worker::valueChanged("Initializing population");
  initializePopulation(lPopulation, lContext, lInitGrowProba, lMinInitDepth, lMaxInitDepth);
  //evaluateSymbReg(lPopulation, lContext, lX, lF);
  evaluateFitness(lPopulation, lContext, trainingIn, trainingOut,Worker::dataset_cols-1,size_training);

  Stats GPthis;
  QString message;
  double bfitTrain,bfitTest,avgSize;
  int bindex; // Best individual index
  calculateStats(lPopulation, 0, message, GPthis.train, bindex, GPthis.avgsize, GPthis.maxsize, GPthis.minsize);
  emit Worker::valueChanged(message);
  float progress_float;
  bool abort = Worker::_abort;
  unsigned int i;
  QString output;
  infix q;
  TreeStruct chosenTree;
  fitnessdata datafit;
  datafit.data = new double*[lNbrGen];
  // prefill population fitness data
  for(i=0; i<lNbrGen; ++i) {
    datafit.data[i] = new double[lPopSize];
    for (int j = 0; j < lPopSize; j++) {
      datafit.data[i][j] = 0;
    }
  }

  // Evolve population for the given number of generations
  std::cout << "Starting evolution" << std::endl;
  emit Worker::valueChanged("Starting evolution");
  for(i=1; i<=lNbrGen; ++i) {
    applySelectionTournament(lPopulation, lContext, lNbrPartTournament);  
    applyCrossover(lPopulation, lContext, lCrossoverProba, lCrossDistribProba, lMaxDepth);
    applyMutationStandard(lPopulation, lContext, lMutStdProba, lMutMaxRegenDepth, lMaxDepth);
    applyMutationSwap(lPopulation, lContext, lMutSwapProba, lMutSwapDistribProba);    
    //evaluateSymbReg(lPopulation, lContext, lX, lF);
    evaluateFitness(lPopulation, lContext, trainingIn, trainingOut,Worker::dataset_cols-1,size_training);
    calculateStats(lPopulation, i, message, GPthis.train, bindex, GPthis.avgsize, GPthis.maxsize, GPthis.minsize);
    evaluateFitnessTesting(lPopulation[bindex],lContext,testingIn,testingOut,Worker::dataset_cols-1,(Worker::dataset_rows-size_training));
    //evaluateFitnessTesting(lPopulation[bindex],lContext,trainingIn,trainingOut,Worker::dataset_cols-1,size_training);
    //GPthis.test = lPopulation[bindex].mFitnessTest;
    GPthis.test = lPopulation[bindex].rFitnessTest;
    GPthis.gen = i;

    lPopulation[bindex].write_qstring(output);
    qDebug()<<i<<" Train: "<<lPopulation[bindex].mFitness<<" Test: "<<lPopulation[bindex].mFitnessTest<<" "<<output;
    //evaluateFitnessTraining(lPopulation[bindex],lContext,trainingIn,trainingOut,Worker::dataset_cols-1,size_training);
    //qDebug()<<i<<" Train: "<<lPopulation[bindex].mFitness;
    output.clear();

    emit Worker::valueChanged(message);
    emit Worker::send_stats(GPthis);
    progress_float = (i/(float)lNbrGen)*100;
    emit Worker::progressChanged((int)progress_float);

    // fill population fitness data
    //datafit.data[i-1] = new double[lPopSize];
    for (int j = 0; j < lPopSize; j++) {
      datafit.data[i-1][j] = lPopulation[j].mFitness;
    }
    emit Worker::plot3DSendData(datafit);
    // Checks if the process should be aborted
    mutex.lock();
    abort = _abort;
    mutex.unlock();

    if (abort) {
      qDebug()<<"Aborting worker process";
      break;
    }
  }

  std::cout << "End of evolution" << std::endl;

  // Outputting best individual
  std::vector<Tree>::const_iterator lBestIndividual = std::max_element(lPopulation.begin(), lPopulation.end());
  std::cout << "Best individual at generation " << (i-1) << " is: ";

  // Visualize best tree
  for(unsigned int i=0;i<lBestIndividual[0].size();i++) {
    chosenTree.mName.append(QString::fromStdString(lBestIndividual[0][i].mPrimitive->getName()));
    chosenTree.mNumberArguments.append(lBestIndividual[0][i].mPrimitive->getNumberArguments());
    chosenTree.mSubTreeSize.append(lBestIndividual[0][i].mSubTreeSize);
    chosenTree.posX.append(0);
    chosenTree.posY.append(0);
    chosenTree.index.append(-1);
  }
  emit Worker::send_tree(chosenTree);

  lBestIndividual[0].write_qstring(output);
  emit Worker::valueChanged("Best individual at generation " + QString::number(i-1) + " is: " + output + " with fitness: " + QString::number(lBestIndividual[0].mFitness));
  std::cout << *lBestIndividual << std:: endl;
  //std::cout << lBestIndividual[0].mFitness << std:: endl;

  //std::cout << "Exiting program" << std::endl << std::flush;

  // Clean up data
  delete inputV;
  delete outputV;
  delete trainingSet;
  delete testingSet;
  emit Worker::GPstarted("Run");
  return 0;
}

unsigned int evaluateFitness(std::vector<Tree>& ioPopulation,
                             Context& ioContext,
                             double* inX,
                             double* inF,int cols, int rows)
{
  //assert(inX.size() == inF.size());
  std::stringstream var;
  double rowV,lQuadErr,lResult,lErr,lRMS;
  unsigned int lNbrEval = 0,i,j,k;
  //qDebug()<<inX[100];
  //for(i=0;i<(cols*rows);i++) qDebug()<<i<<": "<<inX[i];

  for(i=0; i<ioPopulation.size();i++) {
    //if(ioPopulation[i].mValid) continue;
    lQuadErr = 0.0;
    for(j=0; j<rows; j++) {
      // Copy col wise data for variable usage
      for(k=0; k<cols;k++) {
        rowV =  inX[(k*rows)+j];
        var<<"X"<<(k+1);
        ioContext.mPrimitiveMap[var.str()]->setValue(&rowV);
        var.str(std::string());
        //qDebug()<<k<<": "<<rowV;
      }
      lResult = 0.0;
      lErr = 0.0;
      ioPopulation[i].interpret(&lResult, ioContext);
      lErr = lResult - inF[j];
      lQuadErr += (lErr * lErr);                
    }

    lRMS = std::sqrt(lQuadErr / rows);
    ioPopulation[i].mFitness = 1. / (1. + lRMS);
    ioPopulation[i].rFitness = lRMS;
    //ioPopulation[i].mFitness = lRMS;
    ioPopulation[i].mValid = true;
    ++lNbrEval;
  }
  return lNbrEval;
}

unsigned int evaluateFitnessTesting(Tree &individual,
                             Context& ioContext,
                             double* inX,
                             double* inF,int cols, int rows)
{
  std::stringstream var;
  double rowV;
  unsigned int lNbrEval = 0,j,k;
  double lQuadErr = 0.0,lResult,lErr,lRMS;
  //for(j=0;j<(cols*rows);j++) qDebug()<<j<<": "<<inX[j];

  for(j=0; j<rows; j++) {
    // Copy col wise data for variable usage
    for(k=0; k<cols;k++) {
      rowV =  inX[(k*rows)+j];
      var<<"X"<<(k+1);
      ioContext.mPrimitiveMap[var.str()]->setValue(&rowV);
      var.str(std::string());
    }
    lResult = 0.0;
    individual.interpret(&lResult, ioContext);
    lErr = lResult - inF[j];
    lQuadErr += (lErr * lErr);

  }
  lRMS = std::sqrt(lQuadErr / rows);
  individual.mFitnessTest = 1. / (1. + lRMS);
  individual.rFitnessTest = lRMS;
  //individual.mFitnessTest = lRMS;
  individual.mValid = true;
  ++lNbrEval;
  return lNbrEval;
}

unsigned int evaluateFitnessTraining(Tree &individual,
                             Context& ioContext,
                             double* inX,
                             double* inF,int cols, int rows)
{
  std::stringstream var;
  double rowV;
  unsigned int lNbrEval = 0,j,k;
  double lQuadErr = 0.0,lResult,lErr,lRMS;
  //for(j=0;j<(cols*rows);j++) qDebug()<<j<<": "<<inX[j];

  for(j=0; j<rows; j++) {
    // Copy col wise data for variable usage
    for(k=0; k<cols;k++) {
      rowV =  inX[(k*rows)+j];
      var<<"X"<<(k+1);
      ioContext.mPrimitiveMap[var.str()]->setValue(&rowV);
      var.str(std::string());
    }
    lResult = 0.0;
    individual.interpret(&lResult, ioContext);
    lErr = lResult - inF[j];
    lQuadErr += (lErr * lErr);

  }
  lRMS = std::sqrt(lQuadErr / rows);
  individual.mFitness = 1. / (1. + lRMS);
  //individual.mFitness = lRMS;
  //individual.mValid = true;
  ++lNbrEval;
  return lNbrEval;
}

void passTree(Tree &individual,Worker::TreeStruct& tree)
{

}
