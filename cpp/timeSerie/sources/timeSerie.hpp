

class TimeSerie {
    public:
        double operator()(const unsigned int t) const;
        void operator()(const unsigned int t, const double value);
        unsigned int size() const;
        friend std::ostream& operator<<(std::ostream& os, const TimeSerie& timeSerie);
    private:
};