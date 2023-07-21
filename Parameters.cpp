#include "Parameters.h"
#include <exception>
#include <fstream>
#include <iostream>
#include "DefaultActivationFunction.h"
#include "Gudermann.h"
#include "HyperbolicTangent.h"
#include "IllegalArgumentException.h"
#include "Sigmoid.h"

namespace ai {
	
	Parameters::Parameters() {
		
	}
	
	Parameters::Parameters(std::string filePath) /*throw FileNotFoundException*/ {
		this->filePath = filePath;
		std::ifstream file(filePath);
		readFromFile(file);
	}

	std::string const & Parameters::getFilePath() const {
		return filePath;
	}

	std::string const & Parameters::getGASettingsFilePath() const {
		return GASettingsFilePath;
	}

	int Parameters::getGenerationDurationInSeconds() const {
		return generationDurationInSeconds;
	}

	int Parameters::getFrameWidth() const {
		return frameWidth;
	}

	int Parameters::getFrameHeight() const {
		return frameHeight;
	}

	ngn::SharedPtrFunction const & Parameters::getActivationFunction() const {
		return activationFunction;
	}

	ngn::Real Parameters::getMineRadius() const {
		return mineRadius;
	}
	
	ngn::Real Parameters::getMinimumDistanceBetweenMines() const {
		return minimumDistanceBetweenMines;
	}

	ngn::Real Parameters::getMinimumDistanceBetweenSweepers() const {
		return minimumDistanceBetweenSweepers ;
	}

	int Parameters::getNumberOfColumnsOfSpacePartition() const {
		return numberOfColumnsOfSpacePartition;
	}

	/*int Parameters::getNumberOfGenerations() const {
		return numberOfGenerations;
	}*/

	int Parameters::getNumberOfGenerationsOffline() const {
		return numberOfGenerationsOffline;
	}

	int Parameters::getNumberOfGenerationsOnline() const {
		return numberOfGenerationsOnline;
	}

	int Parameters::getNumberOfInputs() const {
		return numberOfInputs;
	}

	ngn::Real Parameters::getMaximumTrackSpeed() const {
		return maximumTrackSpeed;
	}

	ngn::Real Parameters::getMaximumTurnRate() const {
		return maximumTurnRate;
	}

	int Parameters::getNumberOfMines() const {
		return numberOfMines;
	}

	int Parameters::getNumberOfNeuralNetworkLayers() const {
		return numberOfNeuralNetworkLayers;
	}

	std::vector<int> Parameters::getNumberOfNeuronsByNeuralNetworkLayer() const {
		return numberOfNeuronsByNeuralNetworkLayer;
	}

	int Parameters::getNumberOfRowsOfSpacePartition() const {
		return numberOfRowsOfSpacePartition;
	}

	int Parameters::getNumberOfSweepers() const {
		return numberOfSweepers;
	}

	int Parameters::getNumberOfGenerationsBeforePositionReset() const {
		return numberOfGenerationsBeforePositionReset;
	}
	
	ngn::Real Parameters::getParameterOfSigmoidFunction() const {
		return parameterOfSigmoidFunction;
	}

	ngn::Real Parameters::getPhysicsUpdateRate() const {
		return physicsUpdateRate;
	}
	
	ngn::Real Parameters::getSweeperWheelBase() const {
		return sweeperWheelBase;
	}
	
	ngn::Real Parameters::getSweeperWidth() const {
		return sweeperWidth;
	}
	
	ngn::Real Parameters::getSweeperHeight() const {
		return sweeperHeight;
	}
		
	ngn::Vector3D Parameters::getWorldExtents() const {
		return ngn::Vector3D(worldExtentsX, worldExtentsY, worldExtentsZ);
	}

	ngn::Vector3D Parameters::getWorldOrigin() const {
		return ngn::Vector3D(worldOriginX, worldOriginY, worldOriginZ);
	}

	void Parameters::setFilePath(std::string const & filePath) {
		this->filePath = filePath;
	}
	
	void Parameters::setGASettingsFilePath(std::string const & filePath) {
		this->GASettingsFilePath = filePath;
	}
	
	void Parameters::setGenerationDurationInSeconds(int duration) {
		generationDurationInSeconds = duration;
	}
	
	void Parameters::setFrameWidth(int width) {
		frameWidth = width;
	}
	
	void Parameters::setFrameHeight(int height) {
		frameHeight = height;
	}
	
	void Parameters::setActivationFunction(ngn::SharedPtrFunction const & function) {
		activationFunction = function;
	}
	
	void Parameters::setMinimumDistanceBetweenMines(ngn::Real distance) {
		minimumDistanceBetweenMines = distance;
	}
	
	void Parameters::setMinimumDistanceBetweenSweepers(ngn::Real distance) {
		minimumDistanceBetweenSweepers = distance;
	}
	
	void Parameters::setNumberOfColumnsOfSpacePartition(int columns) {
		numberOfColumnsOfSpacePartition = columns;
	}
	
	//void setNumberOfGenerations(int generations);
	void Parameters::setNumberOfGenerationsOffline(int generations) {
		numberOfGenerationsOffline = generations;
	}

	void Parameters::setNumberOfGenerationsOnline(int generations) {
		numberOfGenerationsOnline = generations;
	}
	
	void Parameters::setNumberOfInputs(int nInputs) {
		numberOfInputs = nInputs;
	}
	
	void Parameters::setMaximumTrackSpeed(ngn::Real trackSpeed) {
		maximumTrackSpeed = trackSpeed;
	}
	
	void Parameters::setMaximumTurnRate(ngn::Real turnRate) {
		maximumTurnRate = turnRate;
	}
	
	void Parameters::setNumberOfMines(int nMines) {
		numberOfMines = nMines;
	}
	
	void Parameters::setNumberOfNeuralNetworkLayers(int nLayers) {
		numberOfNeuralNetworkLayers = nLayers;
	}
	
	void Parameters::setNumberOfNeuronsByNeuralNetworkLayer(std::vector<int> const & nNeuronsByLayers) {
		numberOfNeuronsByNeuralNetworkLayer = nNeuronsByLayers;
	}
	
	void Parameters::setNumberOfRowsOfSpacePartition(int rows) {
		numberOfRowsOfSpacePartition = rows;
	}
	
	void Parameters::setNumberOfSweepers(int nSweepers) {
		numberOfSweepers = nSweepers;
	}
	
	void Parameters::setParameterOfSigmoidFunction(ngn::Real param) {
		parameterOfSigmoidFunction = param;
	}
	
	void Parameters::setPhysicsUpdateRate(ngn::Real rate) {
		physicsUpdateRate = rate;
	}
	
	void Parameters::setWorldExtents(ngn::Vector3D extents) {
		worldExtentsX = extents.getX();
		worldExtentsY = extents.getY();
		worldExtentsZ = extents.getZ();
	}
	
	void Parameters::setWorldOrigin(ngn::Vector3D origin) {
		worldOriginX = origin.getX();
		worldOriginY = origin.getY();
		worldOriginZ = origin.getZ();
	}
	
	void Parameters::readFromFile(std::ifstream & file) {
		readNumberOfGenerationsOffline(file);
		readNumberOfGenerationsOnline(file);
		readGASettingsFilePath(file);
		readFrameWidth(file);
		readFrameHeight(file);
		readWorldOriginX(file);
		readWorldOriginY(file);
		readWorldOriginZ(file);
		readWorldExtentsX(file);
		readWorldExtentsY(file);
		readWorldExtentsZ(file);
		readNumberOfRowsOfSpacePartition(file);
		readNumberOfColumnsOfSpacePartition(file);
		readNumberOfSweepers(file);
		readSweeperWheelBase(file);
		readSweeperWidth(file);
		readSweeperHeight(file);
		readMaximumTrackSpeed(file);
		readMaximumTurnRate(file);
		readMinimumDistanceBetweenSweepers(file);
		readNumberOfInputs(file);
		readNumberOfLayersInNeuralNetworks(file);
		readNumberOfNeuronsByLayerInNeuralNetworks(file);
		readNumberOfMines(file);
		readMineRadius(file);
		readMinimumDistanceBetweenMines(file);
		readPhysicsUpdateRate(file);
		readGenerationDurationInSeconds(file);
		readActivationFunction(file);
		readNumberOfGenerationsBeforePositionReset(file);
	}

	
	void Parameters::print(std::ostream & out) const {
		out << "ParametersV2{"
			<< "\nfilePath=" << filePath
			<< ", \nGASettingsFilePath=" << GASettingsFilePath
			<< ", \nframeWidth=" << frameWidth
			<< ", \nframeHeight=" << frameHeight
			<< ", \nworldOriginX=" << worldOriginX
			<< ", \nworldOriginY=" << worldOriginY
			<< ", \nworldOriginY=" << worldOriginZ
			<< ", \nworldExtentsX=" << worldExtentsX
			<< ", \nworldExtentsY=" << worldExtentsY
			<< ", \nworldExtentsY=" << worldExtentsZ
			<< ", \nnumberOfSweepers=" << numberOfSweepers
			<< ", \nmaximumTrackSpeed=" << maximumTrackSpeed
			<< ", \nmaximumTurnRate=" << maximumTurnRate
			<< ", \nminimumDistanceBetweenSweepers=" << minimumDistanceBetweenSweepers
			<< ", \nnumberOfInputs=" << numberOfInputs
			<< ", \nnumberOfNeuralNetworkLayers=" << numberOfNeuralNetworkLayers
			<< ", \nnumberOfNeuronsByNeuralNetworkLayer=\n" << numberOfNeuronsByNeuralNetworkLayerToString()
			<< ", \nnumberOfMines=" << numberOfMines
			<< ", \nminimumDistanceBetweenMines=" << minimumDistanceBetweenMines
			<< ", \nphysicsUpdateRate=" << physicsUpdateRate
			//<< ", \nnumberOfGenerations=" << numberOfGenerations
			<< ", \ngenerationDurationInSeconds=" << generationDurationInSeconds
			<< ", \nparameterOfSigmoidFunction=" << parameterOfSigmoidFunction
			<< ", \nnumberOfGenerationsOffline=" << numberOfGenerationsOffline
			<< ", \nnumberOfGenerationsOnline=" << numberOfGenerationsOnline
			<< ", \nactivationFunctionName=" << activationFunctionName
			<< ", \nactivationFunction=" << activationFunction
			<< ", \nnumberOfGenerationsBeforePositionReset=" << numberOfGenerationsBeforePositionReset
			<< "}\n";
			
		/*std::string filePath;
		std::string GASettingsFilePath;
		int frameWidth;
		int frameHeight;
		int worldOriginX;
		int worldOriginY;
		int worldExtentsX;
		int worldExtentsY;
		int numberOfSweepers;
		ngn::Real maximumTrackSpeed;
		ngn::Real maximumTurnRate;
		ngn::Real minimumDistanceBetweenSweepers;
		int numberOfInputs;
		int numberOfNeuralNetworkLayers;
		std::vector<int> numberOfNeuronsByNeuralNetworkLayer;
		int numberOfMines;
		ngn::Real minimumDistanceBetweenMines;
		int physicsUpdateRate;
		int numberOfGenerations;
		int generationDurationInSeconds;
		ngn::Real parameterOfSigmoidFunction;
		int numberOfGenerationsOffline;
		int numberOfGenerationsOnline;
		std::string activationFunctionName;
		ngn::FunctionSmartPtr activationFunction;
		int numberOfRowsOfSpacePartition;
		int numberOfColumnsOfSpacePartition;*/
	}

	std::string Parameters::numberOfNeuronsByNeuralNetworkLayerToString()const {
		std::string res = "";
		
		for (int unsigned i = 0; i < numberOfNeuronsByNeuralNetworkLayer.size(); ++i) {
			res += "layer_";
			res += std::to_string(i);
			res += ":\t" + std::to_string(numberOfNeuronsByNeuralNetworkLayer.operator [](i));
			res += "\n";
		}
		
		return res;
	}
	
	void Parameters::test() {
		/*std::string parametersFilePath = "/home/john/NetBeansProjects/SmartSweepers/src/smartsweepers/params.ini";
		Parameters parameters = new Parameters(parametersFilePath);

		try {
			try ( FileOutputStream fileOut = new FileOutputStream("/tmp/parameters.ser");  ObjectOutputStream out = new ObjectOutputStream(fileOut)) {
				out.writeObject(parameters);
			}
			System.out.printf("Serialized data is saved in /tmp/parameters.ser");
		} catch (IOException i) {
			System.err.println("IOException");
			System.err.println("i.getClass() = " + i.getClass());
			System.err.println("i.getMessage() = " + i.getMessage());
		}*/
	}
	
	void Parameters::readActivationFunction(std::ifstream & file) {
		readActivationFunctionName(file);

		if (activationFunctionName.compare("Sigmoid") == 0) {
			readSigmoidFunction(file);
		} else if (activationFunctionName.compare("Gudermann") == 0) {
			activationFunction = ngn::SharedPtrFunction(new ngn::Gudermann());
		} else if (activationFunctionName.compare("HyperbolicTangent") == 0) {
			activationFunction = ngn::SharedPtrFunction(new ngn::HyperbolicTangent());
		} else {
			activationFunction = ngn::SharedPtrFunction(new DefaultActivationFunction());
		}
	}

	void Parameters::readSigmoidFunction(std::ifstream & file) {
		std::string tmp; file >> tmp;

		if (tmp.compare("parameter_of_sigmoid_function") != 0) {
			std::string message = "Parameters::readSigmoidFunction(...):\n";
			message += "tmp.compare(\"parameter_of_sigmoid_function\") != 0";
			throw IllegalArgumentException(message);
		}

		file >> parameterOfSigmoidFunction;
		activationFunction = ngn::SharedPtrFunction(new ngn::Sigmoid(parameterOfSigmoidFunction));
	}

	void Parameters::readActivationFunctionName(std::ifstream & file) {
		std::string tmp; file >> tmp;

		if (tmp.compare("activation_function_name") != 0) {
			std::string message = "Parameters::readActivationFunctionName(...):\n";
			message += "tmp.compare(\"activation_function_name\") != 0";
			throw IllegalArgumentException(message);
		}

		file >> activationFunctionName;
	}

	void Parameters::readGenerationDurationInSeconds(std::ifstream & file) {
		std::string tmp; file >> tmp;

		if (tmp.compare("generation_duration_in_seconds") != 0) {
			std::string message = "Parameters::readGenerationDurationInSeconds(...):\n";
			message += "tmp.compare(\"generation_duration_in_seconds\") != 0";
			throw IllegalArgumentException(message);
		}

		file >> generationDurationInSeconds;
	}

	void Parameters::readPhysicsUpdateRate(std::ifstream & file) {
		std::string tmp; file >> tmp;

		if (tmp.compare("physics_update_rate") != 0) {
			std::string message = "Parameters::readPhysicsUpdateRate(...):\n";
			message += "tmp.compare(\"physics_update_rate\") != 0";
			throw IllegalArgumentException(message);
		}

		file >> physicsUpdateRate;
	}

	void Parameters::readMinimumDistanceBetweenMines(std::ifstream & file) {
		std::string tmp; file >> tmp;

		if (tmp.compare("minimum_distance_between_mines") != 0) {
			std::string message = "Parameters::readMinimumDistanceBetweenMines(...):\n";
			message += "tmp.compare(\"minimum_distance_between_mines\") != 0";
			throw IllegalArgumentException(message);
		}

		file >> minimumDistanceBetweenMines;
	}

	void Parameters::readNumberOfMines(std::ifstream & file) {
		std::string tmp; file >> tmp;

		if (tmp.compare("nMines") != 0) {
			std::string message = "Parameters::readNumberOfMines(...):\n";
			message += "tmp.compare(\"nMines\") != 0";
			throw IllegalArgumentException(message);
		}

		file >> numberOfMines;
	}

	void Parameters::readNumberOfNeuronsByLayerInNeuralNetworks(std::ifstream & file) {
		std::string tmp; file >> tmp;

		if (tmp.compare("n_neurons_by_layer") != 0) {
			std::string message = "Parameters::readNumberOfNeuronsByLayerInNeuralNetworks(...):\n";
			message += "tmp.compare(\"n_neurons_by_layer\") != 0";
			throw IllegalArgumentException(message);
		}

		numberOfNeuronsByNeuralNetworkLayer = std::vector<int>();

		for (int i = 0; i < numberOfNeuralNetworkLayers; ++i) {
			int nNeurons;
			file >> nNeurons;
			numberOfNeuronsByNeuralNetworkLayer.push_back(nNeurons);
		}
	}

	void Parameters::readNumberOfLayersInNeuralNetworks(std::ifstream & file) {
		std::string tmp; file >> tmp;

		if (tmp.compare("n_neural_network_layers") != 0) {
			std::string message = "Parameters::readNumberOfLayersInNeuralNetworks(...):\n";
			message += "tmp.compare(\"n_neural_network_layers\") != 0";
			throw IllegalArgumentException(message);
		}

		file >> numberOfNeuralNetworkLayers;
	}

	void Parameters::readNumberOfInputs(std::ifstream & file) {
		std::string tmp; file >> tmp;

		if (tmp.compare("n_neural_network_inputs") != 0) {
			std::string message = "Parameters::readNumberOfInputs(...):\n";
			message += "tmp.compare(\"n_neural_network_inputs\") != 0";
			throw IllegalArgumentException(message);
		}

		file >> numberOfInputs;
	}

	void Parameters::readMaximumTrackSpeed(std::ifstream & file) {
		std::string tmp; file >> tmp;

		if (tmp.compare("maximum_track_speed") != 0) {
			std::string message = "Parameters::readMaximumTrackSpeed(...):\n";
			message += "tmp.compare(\"maximum_track_speed\") != 0";
			throw IllegalArgumentException(message);
		}

		file >> maximumTrackSpeed;
	}

	void Parameters::readMaximumTurnRate(std::ifstream & file) {
		std::string tmp; file >> tmp;

		if (tmp.compare("maximum_turn_rate") != 0) {
			std::string message = "Parameters::readMaximumTurnRate(...):\n";
			message += "tmp.compare(\"maximum_turn_rate\") != 0";
			throw IllegalArgumentException(message);
		}

		file >> maximumTurnRate;
	}

	void Parameters::readMineRadius(std::ifstream & file) {
		std::string tmp; file >> tmp;

		if (tmp.compare("mine_radius") != 0) {
			std::string message = "Parameters::readMineRadius(...):\n";
			message += "tmp.compare(\"mine_radius\") != 0";
			throw IllegalArgumentException(message);
		}

		file >> mineRadius;
	}
	
	void Parameters::readMinimumDistanceBetweenSweepers(std::ifstream & file) {
		std::string tmp; file >> tmp;

		if (tmp.compare("minimum_distance_between_sweepers") != 0) {
			std::string message = "Parameters::readMinimumDistanceBetweenSweepers(...):\n";
			message += "tmp.compare(\"minimum_distance_between_sweepers\") != 0";
			throw IllegalArgumentException(message);
		}

		file >> minimumDistanceBetweenSweepers;
	}

	void Parameters::readNumberOfSweepers(std::ifstream & file) {
		std::string tmp; file >> tmp;

		if (tmp.compare("nSweepers") != 0) {
			std::string message = "Parameters::readNumberOfSweepers(...):\n";
			message += "tmp.compare(\"nSweepers\") != 0";
			throw IllegalArgumentException(message);
		}

		file >> numberOfSweepers;
	}
	
	void Parameters::readWorldExtentsZ(std::ifstream & file) {
		std::string tmp; file >> tmp;

		if (tmp.compare("world_extents_z") != 0) {
			std::string message = "Parameters::readWorldExtentsZ(...):\n";
			message += "tmp.compare(\"world_extents_z\") != 0";
			throw IllegalArgumentException(message);
		}

		file >> worldExtentsZ;
	}
	
	void Parameters::readWorldExtentsY(std::ifstream & file) {
		std::string tmp; file >> tmp;

		if (tmp.compare("world_extents_y") != 0) {
			std::string message = "Parameters::readWorldExtentsY(...):\n";
			message += "tmp.compare(\"world_extents_y\") != 0";
			throw IllegalArgumentException(message);
		}

		file >> worldExtentsY;
	}

	void Parameters::readWorldExtentsX(std::ifstream & file) {
		std::string tmp; file >> tmp;

		if (tmp.compare("world_extents_x") != 0) {
			std::string message = "Parameters::readWorldExtentsX(...):\n";
			message += "tmp.compare(\"world_extents_x\") != 0";
			throw IllegalArgumentException(message);
		}

		file >> worldExtentsX;
	}

	void Parameters::readWorldOriginY(std::ifstream & file) {
		std::string tmp; file >> tmp;

		if (tmp.compare("world_origin_y") != 0) {
			std::string message = "Parameters::readWorldOriginY(...):\n";
			message += "tmp.compare(\"world_origin_y\") != 0";
			throw IllegalArgumentException(message);
		}

		file >> worldOriginY;
	}

	void Parameters::readWorldOriginZ(std::ifstream & file) {
		std::string tmp; file >> tmp;

		if (tmp.compare("world_origin_z") != 0) {
			std::cout << "tmp = " << tmp << "\n";
			std::string message = "Parameters::readWorldOriginZ(...):\n";
			message += "tmp.compare(\"world_origin_z\") != 0";
			throw IllegalArgumentException(message);
		}

		file >> worldOriginZ;
	}
	
	void Parameters::readWorldOriginX(std::ifstream & file) {
		std::string tmp; file >> tmp;

		if (tmp.compare("world_origin_x") != 0) {
			std::string message = "Parameters::readWorldOriginX(...):\n";
			message += "tmp.compare(\"world_origin_x\") != 0";
			throw IllegalArgumentException(message);
		}

		file >> worldOriginX;
	}

	void Parameters::readFrameHeight(std::ifstream & file) {
		std::string tmp; file >> tmp;

		if (tmp.compare("frame_height") != 0) {
			std::string message = "Parameters::readFrameHeight(...):\n";
			message += "tmp.compare(\"frame_height\") != 0";
			throw IllegalArgumentException(message);
		}

		file >> frameHeight;
	}

	void Parameters::readFrameWidth(std::ifstream & file) {
		std::string tmp; file >> tmp;

		if (tmp.compare("frame_width") != 0) {
			std::string message = "Parameters::readFrameWidth(...):\n";
			message += "tmp.compare(\"frame_width\") != 0";
			throw IllegalArgumentException(message);
		}

		file >> frameWidth;
	}

	void Parameters::readGASettingsFilePath(std::ifstream & file) {
		std::string tmp; file >> tmp;

		if (tmp.compare("GA_settings_file_path") != 0) {
			std::string message = "Parameters::readGASettingsFilePath(...):\n";
			message += "tmp.compare(\"GA_settings_file_path\") != 0";
			throw IllegalArgumentException(message);
		}

		file >> GASettingsFilePath;
	}

	void Parameters::readNumberOfGenerationsOnline(std::ifstream & file) {
		std::string tmp; file >> tmp;

		if (tmp.compare("online_number_of_generations") != 0) {
			std::string message = "Parameters::readNumberOfGenerationsOnline(...):\n";
			message += "tmp.compare(\"online_number_of_generations\") != 0";
			throw IllegalArgumentException(message);
		}

		file >> numberOfGenerationsOnline;
	}

	void Parameters::readNumberOfGenerationsOffline(std::ifstream & file) {
		std::string tmp; file >> tmp;

		if (tmp.compare("offline_number_of_generations") != 0) {
			std::string message = "Parameters::readNumberOfGenerationsOffline(...):\n";
			message += "tmp.compare(\"offline_number_of_generations\") != 0";
			throw IllegalArgumentException(message);
		}

		file >> numberOfGenerationsOffline;
	}
	
	void Parameters::readNumberOfRowsOfSpacePartition(std::ifstream & file) {
		std::string tmp; file >> tmp;

		if (tmp.compare("n_rows_of_space_partition") != 0) {
			std::string message = "Parameters::readNumberOfRowsOfSpacePartition(...):\n";
			message += "tmp.compare(\"n_rows_of_space_partition\") != 0";
			throw IllegalArgumentException(message);
		}

		file >> numberOfRowsOfSpacePartition;
	}

	void Parameters::readNumberOfColumnsOfSpacePartition(std::ifstream & file) {
		std::string tmp; file >> tmp;

		if (tmp.compare("n_columns_of_space_partition") != 0) {
			std::string message = "Parameters::readNumberOfColumnsOfSpacePartition(...):\n";
			message += "tmp.compare(\"n_columns_of_space_partition\") != 0";
			throw IllegalArgumentException(message);
		}

		file >> numberOfColumnsOfSpacePartition;
	}
	
	void Parameters::readSweeperWheelBase(std::ifstream & file) {
		std::string tmp; 
		file >> tmp;

		if (tmp.compare("sweeper_wheel_base") != 0) {
			std::string message = "Parameters::readSweeperWheelBase(...):\n";
			message += "tmp.compare(\"sweeper_wheel_base\") != 0";
			throw IllegalArgumentException(message);
		}

		file >> sweeperWheelBase;
	}
	
	void Parameters::readSweeperWidth(std::ifstream & file) {
		std::string tmp; 
		file >> tmp;

		if (tmp.compare("sweeper_width") != 0) {
			std::string message = "Parameters::readSweeperWidth(...):\n";
			message += "tmp.compare(\"sweeper_width\") != 0";
			throw IllegalArgumentException(message);
		}

		file >> sweeperWidth;
	}
	
	void Parameters::readSweeperHeight(std::ifstream & file) {
		std::string tmp; 
		file >> tmp;

		if (tmp.compare("sweeper_height") != 0) {
			std::string message = "Parameters::readSweeperHeight(...):\n";
			message += "tmp.compare(\"sweeper_height\") != 0";
			throw IllegalArgumentException(message);
		}

		file >> sweeperHeight;
	}
		
	void Parameters::readNumberOfGenerationsBeforePositionReset(std::ifstream & file) {
		std::string tmp; 
		file >> tmp;

		if (tmp.compare("reset_positions_after_n_genations") != 0) {
			std::string message = "Parameters::readNumberOfGenerationsBeforePositionReset(...):\n";
			message += "tmp.compare(\"reset_positions_after_n_genations\") != 0";
			throw IllegalArgumentException(message);
		}

		file >> numberOfGenerationsBeforePositionReset;
	}
	
	std::ostream & operator<<(std::ostream & out, Parameters const & params) {
		params.print(out);
		
		return out;
	}
}