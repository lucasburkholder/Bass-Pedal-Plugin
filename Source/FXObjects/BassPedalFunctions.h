inline double dB2Raw(double x) {
    return pow(10.0, x / 20.0);
}

inline double raw2dB(double x) {
    return 20 * log10(x);
}
