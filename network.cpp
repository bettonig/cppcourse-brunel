#include "network.h"


///Network Constructor
Network::Network ()
:neurons_targets(nb_neurons, std::vector<int>(conn_tot)), neurons_(nb_neurons)										// containing each the place (int) of a random neuron it is connected to
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> random_targets(0, nb_neurons-1);
	
	
	for (size_t i(0); i < nb_neurons; ++i) {
		for(size_t j(0); j < conn_tot; ++j) {
			neurons_targets[i][j] = random_targets(gen);
		}
	}
/** This code enables us to iniate the matrix with a random number in each 
 * cases corresponding to a neuron number, so each neurons 'i' will be 
 * connected to randomly chosen neurons.
 */
}																			


///---------------------------------------------------------------------
///---------------------------------------------------------------------




///Network ask method
void Network::ask_display() {

	do {											
		std::cout << "Please insert the starting step ( > 0 & < 10000) at least 1 :" << std::endl;			
		std::cin >> start_step;
		if (std::cin.fail() or start_step >= stop_time) {
			std::cout << "I'm sorry Dave, I'm afraid i can't do that...I think you know what the problem is!" << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		};
	} while (start_step <= 0 or start_step >= stop_time);
	
	
	while (stop_step <= 0 or stop_step < start_step or stop_step > stop_time) {						
		std::cout << "Please insert the stopping step (>beginning step & <=10000) :" << std::endl;	
		std::cin >> stop_step;
		if (std::cin.fail() or stop_step < start_step or stop_step > stop_time) {
			std::cout << "I'm sorry Dave, I'm afraid i can't do that...I think you know what the problem is!" << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		};
	};
		
		
	do {
		std::cout << "Please insert the external current (pA) :" << std::endl;
		std::cin >> Iext;
		if (std::cin.fail()) {
			std::cout << "I'm sorry Dave, I'm afraid i can't do that...I think you know what the problem is!" << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		};
	} while (Iext < 0.0);

/** I found thoses methods on the internet, they made it possible to check 
 * if the input corresponds to what we are expecting without having to create
 * another variable only for control purpose
 * */

}



///---------------------------------------------------------------------
///---------------------------------------------------------------------



///Network running method
void Network::run_rum() 
{		
	
	int lambda(2);
	std::random_device rd_;
	std::mt19937 generate(rd_());
	std::poisson_distribution<> poisson_distribution(lambda);
	
/** Here we generate a random poisson distribution to simulate 
 *  the external input from neurons outside of our simulation
 * */
 	
	std::ofstream Spikes;
	Spikes.open("Spikes_plot.txt");
	
	bool is_Inhib(false);
	Iext2 = Iext;
	
	while (nb_step < stop_time) 
	{	
		for (size_t i(0); i < neurons_.size(); ++i) 
		{									
			if (neurons_[i].Has_now_spiked(/*h*/) and i < (neurons_.size() - 1)) 
			{
				for (size_t j(0); j < conn_tot; ++j) 
				{						
					if (i < nb_exhit) 
					{
						is_Inhib = false;
					} 
					else 
					{
						is_Inhib = true;
					}
					neurons_[i].Send_spike(neurons_[neurons_targets[i][j]], nb_step, is_Inhib);
				}
				//if (nb_step > 5000 and nb_step < 7000) {
					Spikes << nb_step << '\t' << i << std::endl;
				//}
			}
			if (nb_step < start_step or nb_step > stop_step) 
			{
				neurons_[i].Update_state(Iext2, 0);
			} 
			else 
			{
				neurons_[i].Update_state(Iext2, poisson_distribution(generate));
			}
		};
		++nb_step;
	};
	Spikes.close();
}


