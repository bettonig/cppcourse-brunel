#include "neuron.h"
#include <climits>
#include <fstream>
#include <string>
#include <random>
/**	FIRST : 
 * 		This class will create and initiate our vector of neurons & our matrix of connections.
 * 		(for scheme, see commentary in 'network.h')
 * 
 * 		In the vector of neurons, if the neuron is between 1 and 10'000 it is an excitatory neuron,
 * 		if it is between 10'001 and 12'500 it is an inhibitory neuron.
 * 
 * 		For each neurons 'k', A to G (see scheme) are random numbers (between 1 and nb_neurons) that correspond to
 * 		the neurons to which 'k' is connected. 
 * 		Actually they correspond to the places of the neurons in the vector of neurons.
 * 
 * 		The nb of connections 'k' has is 1/10 of the total nb of neurons.
 * 
 * 
 * SECOND :
 * 		The simulation will run from step 0 to step 10'000. But we can choose the interval during which
 * 		the brain is active in some sort (e.g. 2000 to 8888).
 * 
 * THIRD :
 * 		This part is divided into two :
 * 
 * 			1) At each step of the simulation, every neurons is updated, with an external input = to a 
 * 				randomly generated poisson distribution if current-step is between the choosen interval, 
 * 				or with external input = 0 (if outside the choosen interval).
 * 
 * 			2) At each step of the simulation, we check if each neurons has spiked. If Yes, we Send_spike to 
 * 				every neurons it is connected to with the information wether it is an inhibiting or excititing spike.
 * 
 * */
#ifndef NETWORK_H
#define NETWORK_H

class Network {
	
	private:
	
		std::vector<std::vector<int>> neurons_targets;					// neurons_targets : for each i neurons there is j columns of connections,
		std::vector<Neuron> neurons_;									// containing each the place (int) of a random neuron it is connected to
																		// neurons_ : This vector contains the complete list of Neurons
	
		int stop_time = 10000;
		int start_step = 0;
		int stop_step = 0;
		int nb_step = 0;
		//const double h(0.1); //ms										// interval
	
		double Iext = 0.0;		//pA
		double Iext2 = 0.0;		//pA									// Current 
	

		static constexpr int nb_neurons = 12500; 
		static constexpr int nb_exhit = (4*nb_neurons/5); //10000				nb of excitatory Neurons
		static constexpr int nb_inhib = (1*nb_neurons/5); //2500				nb of inhibitory Neurons
	
		static constexpr int exhit_conn = (nb_exhit/10); //1000					nb of connections to an excitatory neuron
		static constexpr int inhib_conn = (nb_inhib/10); //250					nb of connections to an inhibitatory neuron
		static constexpr int conn_tot = (exhit_conn + inhib_conn); //1250		nb of connections total
	
	
	public:
		
		Network();
	
		void ask_display();
		void run_rum();
};
/* SCHEME :
 * 	
 * 			1 - - - - conn_tot
 *		 1					|
 *		 |					|
 *		 |					|
 *		 |					|
 *		 k	A B C D E F	G	|
 *		 |					|
 *		 |					|
 *		 |					|
 * nb_neurons - - - - - - - /
 * 
 * */
#endif
