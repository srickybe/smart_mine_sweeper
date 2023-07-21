#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <boost/shared_ptr.hpp>
#include <iosfwd>
#include <string>
#include <vector>
#include "Function.h"
#include "Real.h"
#include "Vector3D.h"

namespace ai {

	class Parameters {

	public:
		Parameters();
		Parameters(std::string filePath);
		std::string const & getFilePath() const;
		std::string const & getGASettingsFilePath() const;
		int getGenerationDurationInSeconds() const;
		int getFrameWidth() const;
		int getFrameHeight() const;
		ngn::SharedPtrFunction const & getActivationFunction() const;
		ngn::Real getMineRadius() const;
		ngn::Real getMinimumDistanceBetweenMines() const;
		ngn::Real getMinimumDistanceBetweenSweepers() const;
		int getNumberOfColumnsOfSpacePartition() const;
		//int getNumberOfGenerations() const;
		int getNumberOfGenerationsOffline() const;
		int getNumberOfGenerationsOnline() const;
		int getNumberOfInputs() const;
		ngn::Real getMaximumTrackSpeed() const;
		ngn::Real getMaximumTurnRate() const;
		int getNumberOfMines() const;
		int getNumberOfNeuralNetworkLayers() const;
		std::vector<int> getNumberOfNeuronsByNeuralNetworkLayer() const;
		int getNumberOfRowsOfSpacePartition() const;
		int getNumberOfSweepers() const;
		int getNumberOfGenerationsBeforePositionReset() const;
		ngn::Real getParameterOfSigmoidFunction() const;
		ngn::Real getPhysicsUpdateRate() const;
		ngn::Real getSweeperWheelBase() const;
		ngn::Real getSweeperWidth() const;
		ngn::Real getSweeperHeight() const;
		ngn::Vector3D getWorldExtents() const;
		ngn::Vector3D getWorldOrigin() const;
		
		void setFilePath(std::string const & filePath);
		void setGASettingsFilePath(std::string const & filePath);
		void setGenerationDurationInSeconds(int duration);
		void setFrameWidth(int width);
		void setFrameHeight(int height);
		void setActivationFunction(ngn::SharedPtrFunction const & function);
		void setMinimumDistanceBetweenMines(ngn::Real distance);
		void setMinimumDistanceBetweenSweepers(ngn::Real distance);
		void setNumberOfColumnsOfSpacePartition(int columns);
		//int void setNumberOfGenerations();
		void setNumberOfGenerationsOffline(int generations);
		void setNumberOfGenerationsOnline(int generations);
		void setNumberOfInputs(int nInputs);
		void setMaximumTrackSpeed(ngn::Real trackSpeed);
		void setMaximumTurnRate(ngn::Real turnRate);
		void setNumberOfMines(int nMines);
		void setNumberOfNeuralNetworkLayers(int nLayers);
		void setNumberOfNeuronsByNeuralNetworkLayer(std::vector<int> const & nNeuronsByLayers);
		void setNumberOfRowsOfSpacePartition(int rows);
		void setNumberOfSweepers(int nSweepers);
		void setParameterOfSigmoidFunction(ngn::Real param);
		void setPhysicsUpdateRate(ngn::Real rate);
		void setWorldExtents(ngn::Vector3D extents);
		void setWorldOrigin(ngn::Vector3D origin);
		
		
		void readFromFile(std::ifstream & file);
		void print(std::ostream & out) const;
		std::string numberOfNeuronsByNeuralNetworkLayerToString()const;
		void test();
		void readActivationFunction(std::ifstream & file);
		void readSigmoidFunction(std::ifstream & file);
		void readActivationFunctionName(std::ifstream & file);
		void readGenerationDurationInSeconds(std::ifstream & file);
		void readPhysicsUpdateRate(std::ifstream & file);
		void readMinimumDistanceBetweenMines(std::ifstream & file);
		void readNumberOfMines(std::ifstream & file);
		void readNumberOfNeuronsByLayerInNeuralNetworks(std::ifstream & file);
		void readNumberOfLayersInNeuralNetworks(std::ifstream & file);
		void readNumberOfInputs(std::ifstream & file);
		void readMaximumTrackSpeed(std::ifstream & file);
		void readMaximumTurnRate(std::ifstream & file);
		void readMinimumDistanceBetweenSweepers(std::ifstream & file);
		void readNumberOfSweepers(std::ifstream & file);
		void readWorldExtentsZ(std::ifstream & file);
		void readWorldExtentsY(std::ifstream & file);
		void readWorldExtentsX(std::ifstream & file);
		void readWorldOriginZ(std::ifstream & file);
		void readWorldOriginY(std::ifstream & file);
		void readWorldOriginX(std::ifstream & file);
		void readFrameHeight(std::ifstream & file);
		void readFrameWidth(std::ifstream & file);
		void readGASettingsFilePath(std::ifstream & file);
		void readMineRadius(std::ifstream & file);
		void readNumberOfGenerationsOnline(std::ifstream & file);
		void readNumberOfGenerationsOffline(std::ifstream & file);
		void readNumberOfRowsOfSpacePartition(std::ifstream & file);
		void readNumberOfColumnsOfSpacePartition(std::ifstream & file);
		void readNumberOfGenerationsBeforePositionReset(std::ifstream & file);
		void readSweeperWheelBase(std::ifstream & file);
		void readSweeperWidth(std::ifstream & file);
		void readSweeperHeight(std::ifstream & file);
		
	private:
		std::string filePath;
		std::string GASettingsFilePath;
		int frameWidth;
		int frameHeight;
		int worldOriginX;
		int worldOriginY;
		int worldOriginZ;
		int worldExtentsX;
		int worldExtentsY;
		int worldExtentsZ;
		int numberOfSweepers;
		ngn::Real sweeperWheelBase;
		ngn::Real sweeperWidth;
		ngn::Real sweeperHeight;
		ngn::Real maximumTrackSpeed;
		ngn::Real maximumTurnRate;
		ngn::Real minimumDistanceBetweenSweepers;
		int numberOfInputs;
		int numberOfNeuralNetworkLayers;
		std::vector<int> numberOfNeuronsByNeuralNetworkLayer;
		int numberOfMines;
		ngn::Real mineRadius;
		ngn::Real minimumDistanceBetweenMines;
		int physicsUpdateRate;
		//int numberOfGenerations;
		int generationDurationInSeconds;
		ngn::Real parameterOfSigmoidFunction;
		int numberOfGenerationsOffline;
		int numberOfGenerationsOnline;
		std::string activationFunctionName;
		ngn::SharedPtrFunction activationFunction;
		int numberOfRowsOfSpacePartition;
		int numberOfColumnsOfSpacePartition;
		int numberOfGenerationsBeforePositionReset;
	};
	
	std::ostream & operator<<(std::ostream & out, Parameters const & params);
}

#endif // PARAMETERS_H