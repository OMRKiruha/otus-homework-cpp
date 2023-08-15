//
// Created by kiryuhin_ve on 10.08.2023.
//

#ifndef INC_05_HOMEWORK_STATISTICS_H
#define INC_05_HOMEWORK_STATISTICS_H

#include <limits>
#include <cmath>
#include <numeric>
#include <algorithm>

static inline double pct(const std::vector<double>& elements, double percent){
    double m_pct{};
    double i = (elements.size() - 1) * percent;
    int f = floor(i);
    int c = ceil(i);
    if (f == c) {
        m_pct = elements.at(f);
    } else {
        double d0 = elements.at(f) * (c - i);
        double d1 = elements.at(c) * (i - f);
        m_pct = d0 + d1;
    }
    return m_pct;
}

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
    Max() : m_max{std::numeric_limits<double>::lowest()} {}

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
    }

    double eval() const override { return m_summ / m_count; }

    const char *name() const override { return "mean"; }

private:
    double m_summ{};
    int m_count{};
};

class RMSD : public IStatistics {
public:
    RMSD() = default;

    void update(double next) override {
        m_elements.push_back(next);
    }

    double eval() const override {
        long double mean = std::accumulate(m_elements.begin(), m_elements.end(), 0.0L) / m_elements.size();
        long double summOfSquares{};
        for (auto el: m_elements) {
            summOfSquares += powl((el - mean), 2);
        }
        return sqrtl(summOfSquares / (m_elements.size() - 1));
    }

    const char *name() const override { return "std"; }

private:
    std::vector<double> m_elements;
};

class Pct90 : public IStatistics {
public:
    Pct90() = default;

    void update(double next) override {
        m_elements.push_back(next);
        std::sort(m_elements.begin(), m_elements.end());
    }

    double eval() const override {
        return pct(m_elements, 0.90);
    }

    const char *name() const override { return "pct90"; }

private:
    std::vector<double> m_elements;
};

class Pct95 : public IStatistics {
public:
    Pct95() = default;

    void update(double next) override {
        m_elements.push_back(next);
        std::sort(m_elements.begin(), m_elements.end());
    }

    double eval() const override {
        return pct(m_elements, 0.95);
    }

    const char *name() const override { return "pct95"; }

private:
    std::vector<double> m_elements;
};

#endif //INC_05_HOMEWORK_STATISTICS_H
