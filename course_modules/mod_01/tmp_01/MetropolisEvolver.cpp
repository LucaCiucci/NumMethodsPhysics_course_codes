
#include "MetropolisEvolver.hpp"


#include <LC/math/common.hpp>

MetropolisEvolver::MetropolisEvolver() :
	m_gaussianDistribution(0, 1.0),
	m_uniformDistribution(0, 1)
{
	distrib = [](double x) -> double
	{
		constexpr double std_dev = 1;
		constexpr double x0 = 5;
		return 1.0 / (sqrt(lc::_2pi<double>) * std_dev) * exp(-0.5 * lc::sqr(x-x0) / lc::sqr(std_dev));
	};
}

double MetropolisEvolver::step(void)
{
	return this->curr_x = this->next_step();
}

MetropolisSequence MetropolisEvolver::multiStep(size_t N)
{
	MetropolisSequence outcomes;
	outcomes.reserve(N);

	for (size_t i = 0; i < N; i++)
		outcomes.push_back(this->step());

	return outcomes;
}

double MetropolisEvolver::next_step(void)
{
	double x_tilde = this->curr_x + m_gaussianDistribution(m_generator) * delta;

	double p0 = this->distrib(this->curr_x);
	double p1 = this->distrib(x_tilde);

	if (p1 > p0)
		return x_tilde;
	else
		return (m_uniformDistribution(m_generator) < (p1 / p0)) ? x_tilde : this->curr_x;
}

void MetropolisSequence::computeParams(void)
{
	this->computeMean();

	m_c_k.reserve(this->N());

	std::vector<Np> delta; delta.reserve(this->N());
	for (const auto& value : *this)
		delta.push_back(value - this->mean());

	auto arg = [&](size_t i, size_t k)
	{
		return delta[i] * delta[i + k];
	};

	for (size_t k = 0; k < this->N(); k++)
	{
		Np sum_v = 0;
		for (size_t i = 0; i < this->N() - k; i++)
			sum_v += arg(i, k);
		m_c_k.push_back(sum_v / (N() - k));
	}
}

void MetropolisSequence::computeMean(void)
{
	m_mean = 0;
	for (const auto& value : *this)
		m_mean += value;
	m_mean /= N();
}
