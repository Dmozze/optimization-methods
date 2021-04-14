#include <iostream>
#include "first-lab/search-metods.h"
#include "second-lab/Vector.h"
#include "second-lab/Matrix.h"
#include "second-lab/QuadraticFunction.h"
#include "second-lab/gradient_methods.h"
#include "second-lab/Diagonal_Matrix.h"
#include "second-lab/DiagonalQuadraticFunction.h"
#include "second-lab/GeneratorQuadraticFunction.h"
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
    std::cout << M44.determinant() << std::endl;

    std::cout << "test positive definite matrix:\n";
    std::vector<long double> v21 = {2, -1, 0};
    std::vector<long double> v22 = {-1, 2, -1};
    std::vector<long double> v23 = {0, -1, 2};

    Vector V21(v21);
    Vector V22(v22);
    Vector V23(v23);

    std::vector<Vector> m33 = {V21, V22, V23};
    Matrix M33(m33);

    std::cout << M33.is_positive_definite_matrix() << '\n';

    std::cout << "difference vectors:\n";
    Vector vec_prod_3 = V22 * 3;
    Vector vec_diff = V21 - vec_prod_3;
    for (size_t i = 0; i < vec_diff.size(); i++) {
        std::cout << vec_diff[i] << '\n';
    }

}

using T = long double;
using type_B = std::vector<T>;
using type_A = std::vector<type_B>;

T epsilon = 1e-1L;


void first_function() {
    type_A a1 = {{128, 126},
                 {126, 128}};
    type_B b1 = {-10, 30};
    type_B x0 = {1, 1};
    T c1 = 13;
    Matrix A1(a1);
    Vector B1(b1);
    Vector X0(x0);

    QuadraticFunction func1(A1, B1, c1);


    gradient_methods<QuadraticFunction> gm(epsilon);

    gm.gradient_descent(func1, X0, 1.0L/128.0L);

    Vector mi = func1.get_last_calc_vector();
    T miv = func1.get_last_calc_value();

    std::cout << std::setprecision(11);
    std::cout << "min1 vec descent:\n";
    std::cout << mi << '\n';
    std::cout << "min1 value descent:\n";
    std::cout << miv << '\n';
}

void second_function() {
    type_A a = {{2, 0, 0},
              {0, 20, 0},
              {0, 0, 6}};
    type_B b = {23, 17, 1};
    type_B x0 = {0, 0, 0};
    T c = 12;
    Matrix A(a);
    Vector B(b);
    Vector X0(x0);
    QuadraticFunction func(A, B, c);
    gradient_methods<QuadraticFunction> gm(epsilon);
    gm.gradient_descent(func, X0, 1.0L/11.0L);

    std::cout << std::setprecision(11);
    std::cout << "min2 vec descent:\n";
    std::cout << func.get_last_calc_vector() << '\n';
    std::cout << "min2 value descent:\n";
    std::cout << func.get_last_calc_value() << '\n';

}

void first_function_steepest() {
    type_A a1 = {{128, 126},
                 {126, 128}};
    type_B b1 = {-10, 30};
    type_B x0 = {1, 1};
    T c1 = 13;
    Matrix A1(a1);
    Vector B1(b1);
    Vector X0(x0);

    QuadraticFunction func1(A1, B1, c1);


    gradient_methods<QuadraticFunction> gm(epsilon);

    gm.steepest_descent(func1, x0, 254.0L);

    Vector mi = func1.get_last_calc_vector();
    T miv = func1.get_last_calc_value();

    std::cout << std::setprecision(11);
    std::cout << "min1 vec steepest:\n";
    std::cout << mi << '\n';
    std::cout << "min1 value steepest:\n";
    std::cout << miv << '\n';
}

void second_function_steepest() {
    type_A a = {{2, 0, 0},
                {0, 20, 0},
                {0, 0, 6}};
    type_B b = {23, 17, 1};
    type_B x0 = {0, 0, 0};
    T c = 12;
    Matrix A(a);
    Vector B(b);
    Vector X0(x0);
    QuadraticFunction func(A, B, c);
    gradient_methods<QuadraticFunction> gm(epsilon);
    gm.steepest_descent(func, X0, 20.0L);

    std::cout << std::setprecision(11);
    std::cout << "min2 vec steepest:\n";
    std::cout << func.get_last_calc_vector() << '\n';
    std::cout << "min2 value steepest:\n";
    std::cout << func.get_last_calc_value() << '\n';

}

void gradient_descent() {
    first_function();
    second_function();
}

void steepest_descent() {
    first_function_steepest();
    second_function_steepest();
}

void first_function_conjugate() {
    type_A a1 = {{128, 126},
                 {126, 128}};
    type_B b1 = {-10, 30};
    type_B x0 = {1, 1};
    T c1 = 13;
    Matrix A1(a1);
    Vector B1(b1);
    Vector X0(x0);

    QuadraticFunction func1(A1, B1, c1);


    gradient_methods<QuadraticFunction> gm(epsilon);

    gm.conjugate_gradient(func1, X0);

    Vector mi = func1.get_last_calc_vector();
    T miv = func1.get_last_calc_value();

    std::cout << std::setprecision(11);
    std::cout << "min1 vec conjugate:\n";
    std::cout << mi << '\n';
    std::cout << "min1 value conjugate:\n";
    std::cout << miv << '\n';


}


void second_function_conjugate() {
    type_A a = {{2, 0, 0},
                {0, 20, 0},
                {0, 0, 6}};
    type_B b = {23, 17, 1};
    type_B x0 = {0, 0, 0};
    T c = 12;
    Matrix A(a);
    Vector B(b);
    Vector X0(x0);
    QuadraticFunction func(A, B, c);
    gradient_methods<QuadraticFunction> gm(epsilon);
    gm.conjugate_gradient(func, X0);

    std::cout << std::setprecision(11);
    std::cout << "min2 vec conjugate:\n";
    std::cout << func.get_last_calc_vector() << '\n';
    std::cout << "min2 value conjugate:\n";
    std::cout << func.get_last_calc_value() << '\n';
}

void diagonal_test() {
    type_B diag = {2, 20, 6};
    Vector Diag(diag);
    Diagonal_Matrix A(Diag);
    type_B b = {23, 17, 1};
    type_B x0 = {0, 0, 0};
    T c = 12;
    Vector B(b);
    Vector X0(x0);
    DiagonalQuadraticFunction func(A, B, c);
    gradient_methods<DiagonalQuadraticFunction> gm(epsilon);

    gm.gradient_descent(func, X0, 1.0L/11.0L);
    //gm.steepest_descent(func, X0, 20);
    //gm.conjugate_gradient(func, X0);

    std::cout << std::setprecision(11);
    std::cout << "min2 vec diag:\n";
    std::cout << func.get_last_calc_vector() << '\n';
    std::cout << "min2 value diag:\n";
    std::cout << func.get_last_calc_value() << '\n';
}

void conjugate_gradient() {
    first_function_conjugate();
    second_function_conjugate();
}

#define FOR_K_N for (int n = 10; n < 3000; n += 350 + n/200) { for (int k = 1; k < 1500; k += k/5 + 64) {

const std::string generate_quad_string = "generate_quad";
void generator_quad() {
    GeneratorQuadraticFunction gen_quad;
    FOR_K_N
            std::ofstream out(generate_quad_string + '/' + std::to_string(n) + "_" + std::to_string(k));
            DiagonalQuadraticFunction q = gen_quad.gen_diag_quad(n, k);
            Vector diagonalVec = q.hessian().get_diagonal();
            Vector b = q.get_b();
           // out << n << ' ' << k << '\n';
            for (size_t i = 0; i < diagonalVec.size(); i++) {
                out << diagonalVec[i] << ' ';
            }
            out << '\n';
            for (size_t i = 0; i < b.size(); i++) {
                out << b[i] << ' ';
            }
            out << '\n';
            Vector X0 = gen_quad.generateVector(n);
            for (size_t i = 0; i < X0.size(); i++) {
                out << X0[i] << ' ';
            }
            out << std::endl;
            out.close();
        }
    }
}

void generate_tables_descent() {
    using vpair = std::vector<std::pair<int, int>>;
    vpair times_k;
    vpair times_n;
    gradient_methods<DiagonalQuadraticFunction> gm(epsilon);
    std::string path = "tex/descent/";

    FOR_K_N
            std::ifstream input(generate_quad_string + "/" + std::to_string(n) + "_" + std::to_string(k));
            type_B diag(n);
            type_B b(n);
            type_B x0(n);
            T l = 1e9;
            T L = -1e9;
            for (size_t i = 0; i < n; i++) {
                input >> diag[i];
                l = std::min(l, diag[i]);
                L = std::max(L, diag[i]);
            }
            for (size_t i = 0; i < n; i++) {
                input >> b[i];
            }
            for (size_t i = 0; i < n; i++) {
                input >> x0[i];
            }
            Vector Diag(diag);
            Vector B(b);
            Vector X0(x0);
            Diagonal_Matrix DiagM(Diag);
            DiagonalQuadraticFunction quad(DiagM, B, 0.0L);

            size_t cnt = gm.gradient_descent(quad, X0, 2.0L/(l + L));
            times_k.emplace_back(cnt, k);
            times_n.emplace_back(cnt, n);
            input.close();
            std::cout << n << ' ' << k << '\n';
        }
        std::sort(times_k.begin(), times_k.end());
        std::ofstream out_k(path + std::to_string(n) + "k" + csv);
        out_k << "times;k" << std::endl;
        for (auto [a, b] : times_k) {
            out_k << a << ';' << b << std::endl;
        }
        out_k.close();
        times_k.clear();
    }

    std::sort(times_n.begin(), times_n.end(), [](auto a, auto b) {
        return a.second < b.second || a.second == b.second && a.first < b.first;
    });

    std::ofstream out_n(path + "n" + csv);
    out_n << "times;n" << std::endl;
    for (auto [a, b] : times_n) {
        out_n << a << ';' << b << std::endl;
    }
    out_n.close();
};

void generate_tables_steepest() {
    using vpair = std::vector<std::pair<int, int>>;
    vpair times_k;
    vpair times_n;
    gradient_methods<DiagonalQuadraticFunction> gm(epsilon);
    std::string path = "tex/steepest/";

    FOR_K_N
            std::ifstream input(generate_quad_string + "/" + std::to_string(n) + "_" + std::to_string(k));
            type_B diag(n);
            type_B b(n);
            type_B x0(n);
            T l = 1e9;
            T L = -1e9;
            for (size_t i = 0; i < n; i++) {
                input >> diag[i];
                l = std::min(l, diag[i]);
                L = std::max(L, diag[i]);
            }
            for (size_t i = 0; i < n; i++) {
                input >> b[i];
            }
            for (size_t i = 0; i < n; i++) {
                input >> x0[i];
            }
            Vector Diag(diag);
            Vector B(b);
            Vector X0(x0);
            Diagonal_Matrix DiagM(Diag);
            DiagonalQuadraticFunction quad(DiagM, B, 0.0L);

            size_t cnt = gm.steepest_descent(quad, X0, L);
            times_k.emplace_back(cnt, k);
            times_n.emplace_back(cnt, n);
            input.close();
            std::cout << n << ' ' << k << '\n';
        }
        std::sort(times_k.begin(), times_k.end());
        std::ofstream out_k(path + std::to_string(n) + "k" + csv);
        out_k << "times;k" << std::endl;
        for (auto [a, b] : times_k) {
            out_k << a << ';' << b << std::endl;
        }
        out_k.close();
        times_k.clear();
    }

    std::sort(times_n.begin(), times_n.end(), [](auto a, auto b) {
        return a.second < b.second || a.second == b.second && a.first < b.first;
    });

    std::ofstream out_n(path + "n" + csv);
    out_n << "times;n" << std::endl;
    for (auto [a, b] : times_n) {
        out_n << a << ';' << b << std::endl;
    }
    out_n.close();
}

void generate_tables_conjugate() {
    using vpair = std::vector<std::pair<int, int>>;
    vpair times_k;
    vpair times_n;
    gradient_methods<DiagonalQuadraticFunction> gm(epsilon);
    std::string path = "tex/conjugate/";

    FOR_K_N
            std::ifstream input(generate_quad_string + "/" + std::to_string(n) + "_" + std::to_string(k));
            type_B diag(n);
            type_B b(n);
            type_B x0(n);
            T l = 1e9;
            T L = -1e9;
            for (size_t i = 0; i < n; i++) {
                input >> diag[i];
                l = std::min(l, diag[i]);
                L = std::max(L, diag[i]);
            }
            for (size_t i = 0; i < n; i++) {
                input >> b[i];
            }
            for (size_t i = 0; i < n; i++) {
                input >> x0[i];
            }
            Vector Diag(diag);
            Vector B(b);
            Vector X0(x0);
            Diagonal_Matrix DiagM(Diag);
            DiagonalQuadraticFunction quad(DiagM, B, 0.0L);

            size_t cnt = gm.conjugate_gradient(quad, X0);
            times_k.emplace_back(cnt, k);
            times_n.emplace_back(cnt, n);
            input.close();
            std::cout << n << ' ' << k << '\n';
        }
        std::sort(times_k.begin(), times_k.end());
        std::ofstream out_k(path + std::to_string(n) + "k" + csv);
        out_k << "times;k" << std::endl;
        for (auto [a, b] : times_k) {
            out_k << a << ';' << b << std::endl;
        }
        out_k.close();
        times_k.clear();
    }

    std::sort(times_n.begin(), times_n.end(), [](auto a, auto b) {
        return a.second < b.second || a.second == b.second && a.first < b.first;
    });

    std::ofstream out_n(path + "n" + csv);
    out_n << "times;n" << std::endl;
    for (auto [a, b] : times_n) {
        out_n << a << ';' << b << std::endl;
    }
    out_n.close();
}

void second_lab_main() {
    //gradient_descent();
    //steepest_descent();
    //conjugate_gradient();
    //diagonal_test();
    generator_quad();
    generate_tables_descent();
    generate_tables_steepest();
    generate_tables_conjugate();
}

int main() {
    //first_lab_main();
    //test_main();
    second_lab_main();
    return 0;
}