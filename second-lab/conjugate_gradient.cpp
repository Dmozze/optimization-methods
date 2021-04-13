#include "gradient_methods.h"

void gradient_methods::conjugate_gradient(QuadraticFunction &function, Vector &x0) const {

    std::vector<Vector> p;
    Vector gradient0 = function.gradient(x0);
    p.emplace_back(gradient0 * (-1.0L));

    std::vector<Vector> x;
    x.emplace_back(x0);
    function.calc(x.back());

    Vector last_A_pk(x0.size());
    int cnt = 0;
    while (true) {

        if (gradient0.norma() < epsilon) {
            break;
        }

        Vector A_pk = function.hessian() * p.back();
        T A_pk_prod_pk = A_pk * p.back();
        T grad_norma_2 = gradient0 * gradient0;
        T alpha_k = grad_norma_2 / A_pk_prod_pk;

        Vector alpha_pk = p.back() * alpha_k;
        x.emplace_back(x.back() + alpha_pk);
        function.calc(x.back());

        Vector alpha_k_A_pk = A_pk * alpha_k;
        Vector gradient1 = gradient0 + alpha_k_A_pk;

        T bk = (gradient1 * gradient1) / (gradient0 * gradient0);

        Vector bk_pk = p.back() * bk;
        Vector antigradient = gradient1 * (-1.0L);
        p.emplace_back(antigradient + bk_pk);

        gradient0 = gradient1;
    }
}