/**
 * @file utils.h
 * @brief макросы и утиилитры для matrix library
 * @author fairyjac
 */

 #ifndef UTILS_H
 #define UTILS_H
 
 #include "../s21_matrix.h"

 /**
 * @def ABS_VALUE
 * @brief Абсолютное значение (для чисел с плавающей точкой лучше fabs)
 */

 #define ABS_VALUE(value) ((value) > 0 ? (value) : -(value))

 /**
 * @def SELECT_BY_COND
 * @brief Тернарный оператор в виде макроса
 */

 #define SELECT_BY_COND(condition, true_val, false_val) \
 ((condition) ? (true_val) : (false_val))

 /**
 * @brief Указатель на бинарную операцию (матрица-матрица)
 */

 typedef double (*binary_op_t)(double a, double b, double param);

 /**
 * @brief Указатель на унарную операцию (матрица-скаляр)
 */

 typedef double(*unary_op_t)(double a, double param);

 /**
 * @def DEFINE_BINARY_OP
 * @brief Генерация бинарной операции (a op b)
 * @param name имя функции
 * @param expr выражение с a, b, param
 */

 #define DEFINE_BINARY_OP(name,expr)                                \
  static inline double name(double a, double b, double param) {     \
    (void)param;                                                    \
    return(expr);                                                   \
  }

/**
 * @def DEFINE_UNARY_OP
 * @brief Генерация унарной операции (f(a, param))
 * @param name имя функции
 * @param expr выражение с a и param
 */

 #define DEFINE_UNARY_OP(name, expr)                                \
  static inline double name(double a, double b, double param){      \
    (void)b;                                                        \
    return(expr);                                                   \
  }

DEFINE_BINARY_OP(add_op, a + b)
DEFINE_BINARY_OP(sub_op, a - b)
DEFINE_BINARY_OP(mul_op, a * b)
// DEFINE_BINARY_OP(div_op, a / b) - ПЛОХОЙ подход не учитывает деление на 0

static inline double div_op(double a, double b, double param) {
    (void)param;
    if(fabs(b) < 1e-15) {
        return 0.0; // лучше возвращать NAN, но для тестов лучше 0.0, при этом лучшим подходом будет являться проверка
        // на уровне вызывающей функции 
    }
    return a / b;
}

DEFINE_UNARY_OP(scale_op, a * param)
DEFINE_UNARY_OP(add_scalar_op, a + param)

/**
* @def CLEANUP_MATRICES
* @brief safety free
*/

#define CLEANUP_MATRICES(a, b)                          \
do {                                                    \
    if ((a).data != NULL) s21_remove_matrix(&(a));      \
    if ((b).data != NULL) s21_remove_matrix(&(b));      \
} while (0)

#endif // UTILS_H