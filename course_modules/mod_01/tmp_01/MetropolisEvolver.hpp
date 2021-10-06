

#pragma once

#include <random>

#include <functional>

#include <LC/config/config.h>

using lc::Np;

class MetropolisSequence : public std::vector<Np>
{
public:

	size_t N(void) { return this->size(); };
	Np mean(void) { return this->m_mean; };
	Np Ck(size_t k) { return m_c_k[k]; };

	void computeParams(void);

private:

	void computeMean(void);

private:
	Np m_mean = 0;
	std::vector<Np> m_c_k;
};

class MetropolisEvolver
{
public:

	MetropolisEvolver(const MetropolisEvolver&) = default;
	MetropolisEvolver(MetropolisEvolver&&) = default;
	MetropolisEvolver();

	Np step(void);

	MetropolisSequence multiStep(size_t N);

	double next_step(void);

public:
	
	std::function<double(double)> distrib;
	double delta = 0.1;
	double curr_x = 0;

private:
	std::default_random_engine m_generator;
	std::normal_distribution<double> m_gaussianDistribution;
	std::uniform_real_distribution<double> m_uniformDistribution;
};