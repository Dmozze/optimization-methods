#include <iostream>
#include "first-lab/search-metods.h"
#include "second-lab/Vector.h"
#include "second-lab/Matrix.h"
#include <functional>
#include <cmath>
#include <iomanip>
#include <vector>
#include <fstream>

void print(const std::string& s, information_search &inf, std::function<long double(long double)> &func) {
    std::ofstream out(s);
    out << std::setprecision(11);
    inf.r.print(out, func);
    out.flush();
    out.close();
}

const std::string fib = "fibonacci";
const std::string dich = "dichotomy";
const std::string gold = "golden";
const std::string parab = "parabola";
const std::string brent = "brent";
const std::string csv = ".csv";
const std::string path = "tex/tables/";

void print_cnt(const std::string& s, const std::vector<std::pair<long double, int>>& vec) {
    std::ofstream out(path + s + csv);
    out << std::setprecision(15);
    out << "log;cnt" << std::endl;
    for (auto [log_eps, cnt] : vec) {
        out << log_eps << ';' << cnt << std::endl;
    }
    out.flush();
    out.close();
}

void first_lab_main() {
    std::function<long double(long double)> func = [](long double x) {
        return -5 * powl(x, 5) + 4 * powl(x, 4) - 12 * powl(x, 3) + 11 * powl(x, 2) - 2 * x + 1;
    };
    std::function<long double(long double)> func1 = [](long double x) {
        return expl(3.0L * x) + 5.0L * expl(-2.0L * x);
    };
    //break
    std::function<long double(long double)> func2 = [](long double x) {
        return x * sinl(x * x);
    };
    std::cout << std::setprecision(15);
    range r = {-0.5L, 0.5L};
    //range r = {0, 1};
    //range r = {0, 3.7L};//break
    std::string brek = "";
    std::vector<std::pair<long double, int>> dichotomy;
    std::vector<std::pair<long double, int>> fibonacci;
    std::vector<std::pair<long double, int>> golden;
    std::vector<std::pair<long double, int>> parab_vec;
    std::vector<std::pair<long double, int>> brent_vec;
    for (long double epsilon = 1e-1L; epsilon > 1e-11L; epsilon *= 1e-1L) {
        long double log_epsilon = -log10l(epsilon);
        std::cout << epsilon <<  ' ' << log_epsilon << '\n';
        search_methods sm(epsilon);
        information_search dichotomy_answer = sm.dichotomy(func, r);
        std::cout << "dichotomy: " << dichotomy_answer.point << ' ' << dichotomy_answer.value << ' ' << dichotomy_answer.times << std::endl;
        information_search fib_answer = sm.fibonacci(func, r);
        std::cout << "fibonacci: " << fib_answer.point << ' ' << fib_answer.value << ' ' << fib_answer.times << std::endl;
        information_search golden_answer = sm.golden_ratio(func, r);
        std::cout << "golden: " << golden_answer.point << ' ' << golden_answer.value << ' ' << golden_answer.times << std::endl;
        information_search parabolas = sm.parabolas(func, r);
        std::cout << "parabolas: " << parabolas.point << ' ' << parabolas.value << ' ' << parabolas.times << std::endl;
        information_search brent_answer = sm.combined_brent(func, r);
        std::cout << "brent: " << brent_answer.point << ' ' << brent_answer.value << ' ' << brent_answer.times << std::endl;
        std::cout << parabolas.value - dichotomy_answer.value << std::endl;
        std::cout << fib_answer.value - dichotomy_answer.value << std::endl;
        std::cout << golden_answer.value - dichotomy_answer.value << std::endl;
        std::cout << brent_answer.value - dichotomy_answer.value << std::endl;
        std::cout << dichotomy_answer.times - fib_answer.times << std::endl;
        std::cout << dichotomy_answer.times - golden_answer.times << std::endl;
        std::cout << "\n*************\n\n";
        dichotomy.emplace_back(log_epsilon, dichotomy_answer.times);
        fibonacci.emplace_back(log_epsilon, fib_answer.times);
        golden.emplace_back(log_epsilon, golden_answer.times);
        parab_vec.emplace_back(log_epsilon, parabolas.times);
        brent_vec.emplace_back(log_epsilon, brent_answer.times);
        std::ostringstream s;
        s << std::setprecision(15) << epsilon;
        print(path + dich + brek + s.str() + csv, dichotomy_answer, func);
        print(path + fib + brek + s.str() + csv, fib_answer, func);
        print(path + gold + brek + s.str() + csv, golden_answer, func);
        print(path + parab + brek + s.str() + csv, parabolas, func);
        print(path + brent + brek + s.str() + csv, brent_answer, func);
        sm.research_parabolas(func, r, 0.01L);
    }

    print_cnt(dich + brek, dichotomy);
    print_cnt(fib + brek, fibonacci);
    print_cnt(gold + brek, golden);
    print_cnt(parab + brek, parab_vec);
    print_cnt(brent + brek, brent_vec);
}


void test_main() {
    std::vector<long double> v1 = {1, 2, 3};
    std::vector<long double> v2 = {4, 5, 6};
    std::vector<long double> v3 = {7, 8, 9};
    Vector V1(v1);
    Vector V2(v2);
    Vector V3(v3);

    std::vector<Vector> m = {V1, V2, V3};
    Matrix M(m);

    std::vector<long double> v11 = {1, 1, 1};
    std::vector<long double> v12 = {1, 1, 1};
    std::vector<long double> v13 = {1, 1, 1};
    std::vector<long double> v_pifagor = {3, 4, 0};
    std::vector<long double> v_good = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    Vector V11(v11);
    Vector V12(v12);
    Vector V13(v13);
    Vector V_pifagor(v_pifagor);
    Vector V_good(v_good);

    std::vector<Vector> m1 = {V11, V12, V13};
    Matrix M1(m1);

    Matrix M11 = M1 * 2;
    Matrix MM = M + M1;
    Matrix MM2 = M * M1;
    Vector VV = M * V1;

    for (size_t j = 0; j < M11.size(); j++) {
        for (size_t i = 0; i < M11.size(); i++) {
            std::cout << M11[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
    for (size_t j = 0; j < MM.size(); j++) {
        for (size_t i = 0; i < MM.size(); i++) {
            std::cout << MM[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
    for (size_t j = 0; j < MM2.size(); j++) {
        for (size_t i = 0; i < MM2.size(); i++) {
            std::cout << MM2[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';

    for (size_t i = 0; i < VV.size(); i++) {
        std::cout << VV[i] << '\n';
    }
    std::cout << "norma VV: " << VV.norma();
    std::cout << '\n';
    std::cout << "norma V11: " << V11.norma();
    std::cout << '\n';
    std::cout << "norma V_pifagor: " << V_pifagor.norma();
    std::cout << '\n';
    std::cout << "V_good:\n";
    for (size_t i = 0; i < V_good.size(); i++) {
        std::cout << V_good[i] << '\n';
    }
    std::cout << "norma V_good: " << V_good.norma() << '\n';

    std::cout << "determinant:\n";
    std::cout << MM.determinant() << '\n';

    std::vector<long double> v41 = {-2, 3, -5, 4};
    std::vector<long double> v42 = {1, 0, 2, -  1};
    std::vector<long double> v43 = {3, -1, 3, 2};
    std::vector<long double> v44 = {2, 2, 0, -3};

    Vector V41(v41);
    Vector V42(v42);
    Vector V43(v43);
    Vector V44(v44);

    std::vector<Vector> m44 = {V41, V42, V43, V44};

    Matrix M44(m44);

    std::cout << "determinant 4x4:\n";
    std::cout << M44.determinant();

}


void second_lab_main() {

}

int main() {
    //first_lab_main();
    test_main();
    second_lab_main();
    return 0;
}