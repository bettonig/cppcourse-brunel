#include <iostream>
#include "neuron.h"
#include "gtest/gtest.h"


	static constexpr double tau_ = 20;
	//static constexpr double threshold_ = 20;
	static constexpr double c_ = 1.0;
	//static constexpr double J_ = 0.1; //0.1
	//static constexpr int refractory_time_ = 20;
	//static constexpr int delay = 15;	
	
	double Exp_ = exp(-(0.1/tau_));
	static constexpr double c2 = tau_/c_;




TEST (NeuronTest, MembranePotential) {
	Neuron neuron;
	
	neuron.Update_state(1.0, 0);
	EXPECT_EQ(1.0 * c2 * (1 - Exp_), neuron.Get_membrane_potential());
}
/** This function tests if update_state works fine
 * */
 

TEST (NeuronTest, StoreSpikeExcit_n_Buffer) {
	Neuron neuron1;
	
	neuron1.Store_spike(20 , false);
	EXPECT_EQ(neuron1.Get_buffer(3), 1);
}
/** This function tests both if store_spike and the buffer works (with an excitator input)
 * */


TEST (NeuronTest, StoreSpikeInhib_n_Buffer) {
	Neuron neuron2;
	
	neuron2.Store_spike(20, true);
	EXPECT_EQ(neuron2.Get_buffer(3), -5);
}
/** This function tests if both store_spike and the buffer works (with an inhibitor input)
 * */


TEST (NeuronTest, SendSpikesExcit) {
	Neuron neuron3;
	Neuron neuron4;
	
	neuron3.Send_spike(neuron4, 10, false);
	EXPECT_EQ(neuron4.Get_buffer(9), 1);
}
/** This function tests both if send_spike and the buffer works (with excitator input)
 * */


TEST (NeuronTest, SendSpikesInhib) {
	Neuron neuron3;
	Neuron neuron4;
	
	neuron3.Send_spike(neuron4, 10, true);
	EXPECT_EQ(neuron4.Get_buffer(9), -5);
}
/** This function tests both if send_spike and the buffer works (with inhibitor input)
 * */


TEST (NeuronTest, UpdateState100) {
	Neuron neuron5;
	
	for (size_t i(0); i < 2000; ++i) {
		neuron5.Update_state(1.0, 0);
	}
	
	EXPECT_EQ(neuron5.Get_nb_spks(), 0);
}
/** This test makes sure that with an external current of 1.0 pA, the neuron doesn't spike
 * */


TEST (NeuronTest, UpdateState101) {
	Neuron neuron6;
	
	for (size_t i(0); i < 924; ++i) {
		neuron6.Update_state(1.01, 0);
	}
	
	EXPECT_EQ(neuron6.Has_now_spiked(), true);
}
/** This test makes sure that with an external current of 1.01 pA, the neuron spikes at step 924
 * */


TEST (NeuronTest, IsRefractory) {
	Neuron neuron7;
	
	for (size_t i(0); i < 923; ++i) {
		neuron7.Update_state(1.01, 0);
	}
	
	EXPECT_EQ(neuron7.Is_refractory(), false);
	
	for (size_t i(0); i < 20; ++i) {
		neuron7.Update_state(1.01, 0);
	}
	
	EXPECT_EQ(neuron7.Is_refractory(), true);
	
		neuron7.Update_state(1.01, 0);
		
	EXPECT_EQ(neuron7.Is_refractory(), false);
}
/** This function makes sure that a neuron is refractory only for 20 steps after the spike
 * */


int main(int argc, char **argv) 
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
