//
// Created by kiryuhin_ve on 10.08.2023.
//

#ifndef INC_05_HOMEWORK_STATISTICS_H
#define INC_05_HOMEWORK_STATISTICS_H

#include <limits>
#include <cmath>
#include <numeric>
#include <algorithm>

class IStatistics {
public:
    virtual ~IStatistics() = default;

    virtual void update(double next) = 0;

    virtual double eval() const = 0;

    virtual const char *name() const = 0;
};

class Min : public IStatistics {
public:
    Min() : m_min{std::numeric_limits<double>::max()} {
    }

    void update(double next) override {
        if (next < m_min) {
            m_min = next;
        }
    }

    double eval() const override {
        return m_min;
    }

    const char *name() const override {
        return "min";
    }

private:
    double m_min;
};

class Max : public IStatistics {
public:
    Max() : m_max{std::numeric_limits<double>::min()} {}

    void update(double next) override {
        if (next > m_max) {
            m_max = next;
        }
    }

    double eval() const override { return m_max; }

    const char *name() const override { return "max"; }

private:
    double m_max;
};

class Mean : public IStatistics {
public:
    Mean() = default;

    void update(double next) override {
        m_summ += next;
        ++m_count;
        m_mean = m_summ / m_count;
    }

    double eval() const override { return m_mean; }

    const char *name() const override { return "mean"; }

private:
    double m_mean{};
    double m_summ{};
    int m_count{};
};

class RMSD : public IStatistics {
public:
    RMSD() = default;

    void update(double next) override {
        m_elements.push_back(next);
        long double mean = std::accumulate(m_elements.begin(), m_elements.end(), 0.0L) / m_elements.size();
        long double summOfSquares{};
        for (auto el: m_elements) {
            summOfSquares += powl((el - mean), 2);
        }
        m_std = sqrtl(summOfSquares / (m_elements.size() - 1));
    }

    double eval() const override { return m_std; }

    const char *name() const override { return "std"; }

private:
    double m_std{};
    std::vector<double> m_elements;
};

class Pct90 : public IStatistics {
public:
    Pct90() = default;

    void update(double next) override {
        m_elements.push_back(next);
        std::sort(m_elements.begin(), m_elements.end());
        double i = (m_elements.size() - 1) * 0.9;
        int f = floor(i);
        int c = ceil(i);
        if (f == c) {
            m_pct90 = m_elements.at(f);
        } else {
            double d0 = m_elements.at(f) * (c - i);
            double d1 = m_elements.at(c) * (i - f);
            m_pct90 = d0 + d1;
        }
    }

    double eval() const override { return m_pct90; }

    const char *name() const override { return "pct90"; }

private:
    double m_pct90{};
    std::vector<double> m_elements;
};

class Pct95 : public IStatistics {
public:
    Pct95() = default;

    void update(double next) override {
        m_elements.push_back(next);
        std::sort(m_elements.begin(), m_elements.end());
        double i = (m_elements.size() - 1) * 0.95;
        int f = floor(i);
        int c = ceil(i);
        if (f == c) {
            m_pct95 = m_elements.at(f);
        } else {
            double d0 = m_elements.at(f) * (c - i);
            double d1 = m_elements.at(c) * (i - f);
            m_pct95 = d0 + d1;
        }
    }

    double eval() const override { return m_pct95; }

    const char *name() const override { return "pct95"; }

private:
    double m_pct95{};
    std::vector<double> m_elements;
};

#endif //INC_05_HOMEWORK_STATISTICS_H
