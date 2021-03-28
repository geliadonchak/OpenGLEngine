#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <stdio.h>

#include "../Matrix.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define EPS 10e-6
#define DET_EPS 10e-3

template<typename T>
void compare_vectors(T glm_vector, const Vector &my_vec) {
    for (int i = 0; i < my_vec.size(); ++i) {
        REQUIRE(std::abs(glm_vector[i] - my_vec[i]) < EPS);
    }
}

template<typename T>
void compare_matrix(T glm_matrix, const Matrix &my_mat) {
    for (int i = 0; i < my_mat.size(); ++i) {
        for (int j = 0; j < my_mat.size(); ++j) {
            REQUIRE(std::abs(glm_matrix[i][j] - my_mat[i][j]) < EPS);
        }
    }
}

TEST_CASE("Vector testing") {

    SECTION("Construction of vectors, getters") {
        auto *numbers2 = new float[2];
        numbers2[0] = 34.7;
        numbers2[1] = -57.12;

        auto *numbers3 = new float[3];
        numbers3[0] = 17;
        numbers3[1] = 39.272;
        numbers3[2] = -38;

        auto *numbers4 = new float[4];
        numbers4[0] = 74;
        numbers4[1] = 8.467;
        numbers4[2] = -253;
        numbers4[3] = -83.382;

        std::vector<Vector> my_vectors2 = {
                Vector(2),
                Vector(2, -4.36),
                Vector{11.3, 4},
                Vector(Vector(2)),
                Vector(2, numbers2)
        };

        std::vector<Vector> my_vectors3 = {
                Vector(3),
                Vector(3, 7.01),
                Vector{23.22, -13.09, 9},
                Vector(Vector(3)),
                Vector(3, numbers3)
        };

        std::vector<Vector> my_vectors4 = {
                Vector(4),
                Vector(4, 19.562),
                Vector{93.293, 17.1, -133, -82.001},
                Vector(Vector(4)),
                Vector(4, numbers4)
        };

        std::vector<glm::vec2> glm_vectors2 = {
                glm::vec2(),
                glm::vec2(-4.36),
                glm::vec2(11.3, 4),
                glm::vec2(glm::vec2())
        };

        std::vector<glm::vec3> glm_vectors3 = {
                glm::vec3(),
                glm::vec3(7.01),
                glm::vec3(23.22, -13.09, 9),
                glm::vec3(glm::vec3())
        };

        std::vector<glm::vec4> glm_vectors4 = {
                glm::vec4(),
                glm::vec4(19.562),
                glm::vec4(93.293, 17.1, -133, -82.001),
                glm::vec4(glm::vec4())
        };

        for (int i = 0; i < 4; ++i) {
            REQUIRE(2 == my_vectors2[i].size());
            compare_vectors<glm::vec2>(glm_vectors2[i], my_vectors2[i]);
        }

        for (int i = 0; i < 4; ++i) {
            REQUIRE(3 == my_vectors3[i].size());
            compare_vectors<glm::vec3>(glm_vectors3[i], my_vectors3[i]);
        }

        for (int i = 0; i < 4; ++i) {
            REQUIRE(4 == my_vectors4[i].size());
            compare_vectors<glm::vec4>(glm_vectors4[i], my_vectors4[i]);
        }
    }

    SECTION("Copy of vectors with assignment operator") {
        std::vector<Vector> my_vectors = {
                Vector(2),
                Vector(2, -4.36),
                Vector{11.3, 4},
                Vector(3),
                Vector(3, 7.01),
                Vector{23.22, -13.09, 9},
                Vector(4),
                Vector(4, 19.562),
                Vector{93.293, 17.1, -133, -82.001}
        };

        for (auto vec: my_vectors) {
            Vector vec_copy(1);
            vec_copy = vec;
            REQUIRE(vec_copy == vec);

            vec = vec;
            REQUIRE(vec == vec);
        }
    }

    SECTION("Vector addition") {
        std::vector<Vector> my_vectors2 = {
                Vector(2),
                Vector(2, -4.36),
                Vector{11.3, 4},
                Vector(Vector(2))
        };

        std::vector<Vector> my_vectors3 = {
                Vector(3),
                Vector(3, 7.01),
                Vector{23.22, -13.09, 9},
                Vector(Vector(3))
        };

        std::vector<Vector> my_vectors4 = {
                Vector(4),
                Vector(4, 19.562),
                Vector{93.293, 17.1, -133, -82.001},
                Vector(Vector(4))
        };

        std::vector<glm::vec2> glm_vectors2 = {
                glm::vec2(),
                glm::vec2(-4.36),
                glm::vec2(11.3, 4),
                glm::vec2(glm::vec2())
        };

        std::vector<glm::vec3> glm_vectors3 = {
                glm::vec3(),
                glm::vec3(7.01),
                glm::vec3(23.22, -13.09, 9),
                glm::vec3(glm::vec3())
        };

        std::vector<glm::vec4> glm_vectors4 = {
                glm::vec4(),
                glm::vec4(19.562),
                glm::vec4(93.293, 17.1, -133, -82.001),
                glm::vec4(glm::vec4())
        };

        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                Vector res = my_vectors2[i] + my_vectors2[j];
                glm::vec2 glm_res = glm_vectors2[i] + glm_vectors2[j];
                compare_vectors<glm::vec2>(glm_res, res);
            }
        }

        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                Vector res = my_vectors3[i] + my_vectors3[j];
                glm::vec3 glm_res = glm_vectors3[i] + glm_vectors3[j];
                compare_vectors<glm::vec3>(glm_res, res);
            }
        }

        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                Vector res = my_vectors4[i] + my_vectors4[j];
                glm::vec4 glm_res = glm_vectors4[i] + glm_vectors4[j];
                compare_vectors<glm::vec4>(glm_res, res);
            }
        }

        for (int i = 0; i < 3; ++i) {
            my_vectors2[i] += my_vectors2[i + 1];
            glm_vectors2[i] += glm_vectors2[i + 1];
            compare_vectors<glm::vec2>(glm_vectors2[i], my_vectors2[i]);
        }

        for (int i = 0; i < 3; ++i) {
            my_vectors3[i] += my_vectors3[i + 1];
            glm_vectors3[i] += glm_vectors3[i + 1];
            compare_vectors<glm::vec3>(glm_vectors3[i], my_vectors3[i]);
        }

        for (int i = 0; i < 3; ++i) {
            my_vectors4[i] += my_vectors4[i + 1];
            glm_vectors4[i] += glm_vectors4[i + 1];
            compare_vectors<glm::vec4>(glm_vectors4[i], my_vectors4[i]);
        }

        REQUIRE_THROWS(my_vectors2[0] + my_vectors3[0]);
    }

    SECTION("Vector subtraction") {
        std::vector<Vector> my_vectors2 = {
                Vector(2),
                Vector(2, -4.36),
                Vector{11.3, 4},
                Vector(Vector(2))
        };

        std::vector<Vector> my_vectors3 = {
                Vector(3),
                Vector(3, 7.01),
                Vector{23.22, -13.09, 9},
                Vector(Vector(3))
        };

        std::vector<Vector> my_vectors4 = {
                Vector(4),
                Vector(4, 19.562),
                Vector{93.293, 17.1, -133, -82.001},
                Vector(Vector(4))
        };

        std::vector<glm::vec2> glm_vectors2 = {
                glm::vec2(),
                glm::vec2(-4.36),
                glm::vec2(11.3, 4),
                glm::vec2(glm::vec2())
        };

        std::vector<glm::vec3> glm_vectors3 = {
                glm::vec3(),
                glm::vec3(7.01),
                glm::vec3(23.22, -13.09, 9),
                glm::vec3(glm::vec3())
        };

        std::vector<glm::vec4> glm_vectors4 = {
                glm::vec4(),
                glm::vec4(19.562),
                glm::vec4(93.293, 17.1, -133, -82.001),
                glm::vec4(glm::vec4())
        };

        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                Vector res = my_vectors2[i] - my_vectors2[j];
                glm::vec2 glm_res = glm_vectors2[i] - glm_vectors2[j];
                compare_vectors<glm::vec2>(glm_res, res);
            }
        }

        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                Vector res = my_vectors3[i] - my_vectors3[j];
                glm::vec3 glm_res = glm_vectors3[i] - glm_vectors3[j];
                compare_vectors<glm::vec3>(glm_res, res);
            }
        }

        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                Vector res = my_vectors4[i] - my_vectors4[j];
                glm::vec4 glm_res = glm_vectors4[i] - glm_vectors4[j];
                compare_vectors<glm::vec4>(glm_res, res);
            }
        }

        for (int i = 0; i < 3; ++i) {
            my_vectors2[i] -= my_vectors2[i + 1];
            glm_vectors2[i] -= glm_vectors2[i + 1];
            compare_vectors<glm::vec2>(glm_vectors2[i], my_vectors2[i]);
        }

        for (int i = 0; i < 3; ++i) {
            my_vectors3[i] -= my_vectors3[i + 1];
            glm_vectors3[i] -= glm_vectors3[i + 1];
            compare_vectors<glm::vec3>(glm_vectors3[i], my_vectors3[i]);
        }

        for (int i = 0; i < 3; ++i) {
            my_vectors4[i] -= my_vectors4[i + 1];
            glm_vectors4[i] -= glm_vectors4[i + 1];
            compare_vectors<glm::vec4>(glm_vectors4[i], my_vectors4[i]);
        }
    }

    SECTION("Scalar product of vectors") {
        std::vector<Vector> my_vectors2 = {
                Vector(2),
                Vector(2, -4.36),
                Vector{11.3, 4},
                Vector(Vector(2))
        };

        std::vector<Vector> my_vectors3 = {
                Vector(3),
                Vector(3, 7.01),
                Vector{23.22, -13.09, 9},
                Vector(Vector(3))
        };

        std::vector<Vector> my_vectors4 = {
                Vector(4),
                Vector(4, 19.562),
                Vector{93.293, 17.1, -133, -82.001},
                Vector(Vector(4))
        };

        std::vector<glm::vec2> glm_vectors2 = {
                glm::vec2(),
                glm::vec2(-4.36),
                glm::vec2(11.3, 4),
                glm::vec2(glm::vec2())
        };

        std::vector<glm::vec3> glm_vectors3 = {
                glm::vec3(),
                glm::vec3(7.01),
                glm::vec3(23.22, -13.09, 9),
                glm::vec3(glm::vec3())
        };

        std::vector<glm::vec4> glm_vectors4 = {
                glm::vec4(),
                glm::vec4(19.562),
                glm::vec4(93.293, 17.1, -133, -82.001),
                glm::vec4(glm::vec4())
        };

        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                float res = my_vectors2[i].scalar_product(my_vectors2[j]);
                float glm_res = glm::dot(glm_vectors2[i], glm_vectors2[j]);
                REQUIRE(std::abs(res - glm_res) < EPS);
            }
        }

        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                float res = my_vectors3[i].scalar_product(my_vectors3[j]);
                float glm_res = glm::dot(glm_vectors3[i], glm_vectors3[j]);
                REQUIRE(std::abs(res - glm_res) < EPS);
            }
        }

        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                float res = my_vectors4[i].scalar_product(my_vectors4[j]);
                float glm_res = glm::dot(glm_vectors4[i], glm_vectors4[j]);
                REQUIRE(std::abs(res - glm_res) < EPS);
            }
        }
    }

    SECTION("Cross product of vectors") {
        std::vector<Vector> my_vectors3 = {
                Vector(3),
                Vector(3, 7.01),
                Vector{23.22, -13.09, 9},
                Vector(Vector(3))
        };

        std::vector<glm::vec3> glm_vectors3 = {
                glm::vec3(),
                glm::vec3(7.01),
                glm::vec3(23.22, -13.09, 9),
                glm::vec3(glm::vec3())
        };

        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                Vector res = Vector::cross_product(my_vectors3[i], my_vectors3[j]);
                glm::vec3 glm_res = glm::cross(glm_vectors3[i], glm_vectors3[j]);
                compare_vectors<glm::vec3>(glm_res, res);
            }
        }

        REQUIRE_THROWS(Vector::cross_product(my_vectors3[0], Vector(2)));
    }

    SECTION("Multiply vector by float") {
        std::vector<Vector> my_vectors2 = {
                Vector(2),
                Vector(2, -4.36),
                Vector{11.3, 4},
                Vector(Vector(2))
        };

        std::vector<Vector> my_vectors3 = {
                Vector(3),
                Vector(3, 7.01),
                Vector{23.22, -13.09, 9},
                Vector(Vector(3))
        };

        std::vector<Vector> my_vectors4 = {
                Vector(4),
                Vector(4, 19.562),
                Vector{93.293, 17.1, -133, -82.001},
                Vector(Vector(4))
        };

        std::vector<glm::vec2> glm_vectors2 = {
                glm::vec2(),
                glm::vec2(-4.36),
                glm::vec2(11.3, 4),
                glm::vec2(glm::vec2())
        };

        std::vector<glm::vec3> glm_vectors3 = {
                glm::vec3(),
                glm::vec3(7.01),
                glm::vec3(23.22, -13.09, 9),
                glm::vec3(glm::vec3())
        };

        std::vector<glm::vec4> glm_vectors4 = {
                glm::vec4(),
                glm::vec4(19.562),
                glm::vec4(93.293, 17.1, -133, -82.001),
                glm::vec4(glm::vec4())
        };

        std::vector<float> numbers{4.2, -4.2, 0.0};

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                Vector res = my_vectors2[i] * num;
                glm::vec2 glm_res = glm_vectors2[i] * num;
                compare_vectors<glm::vec2>(glm_res, res);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                Vector res = my_vectors3[i] * num;
                glm::vec3 glm_res = glm_vectors3[i] * num;
                compare_vectors<glm::vec3>(glm_res, res);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                Vector res = my_vectors4[i] * num;
                glm::vec4 glm_res = glm_vectors4[i] * num;
                compare_vectors<glm::vec4>(glm_res, res);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                my_vectors2[i] *= num;
                glm_vectors2[i] *= num;
                compare_vectors<glm::vec2>(glm_vectors2[i], my_vectors2[i]);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                my_vectors3[i] *= num;
                glm_vectors3[i] *= num;
                compare_vectors<glm::vec3>(glm_vectors3[i], my_vectors3[i]);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                my_vectors4[i] *= num;
                glm_vectors4[i] *= num;
                compare_vectors<glm::vec4>(glm_vectors4[i], my_vectors4[i]);
            }
        }
    }

    SECTION("Divide vector by float") {
        std::vector<Vector> my_vectors2 = {
                Vector(2),
                Vector(2, -4.36),
                Vector{11.3, 4},
                Vector(Vector(2))
        };

        std::vector<Vector> my_vectors3 = {
                Vector(3),
                Vector(3, 7.01),
                Vector{23.22, -13.09, 9},
                Vector(Vector(3))
        };

        std::vector<Vector> my_vectors4 = {
                Vector(4),
                Vector(4, 19.562),
                Vector{93.293, 17.1, -133, -82.001},
                Vector(Vector(4))
        };

        std::vector<glm::vec2> glm_vectors2 = {
                glm::vec2(),
                glm::vec2(-4.36),
                glm::vec2(11.3, 4),
                glm::vec2(glm::vec2())
        };

        std::vector<glm::vec3> glm_vectors3 = {
                glm::vec3(),
                glm::vec3(7.01),
                glm::vec3(23.22, -13.09, 9),
                glm::vec3(glm::vec3())
        };

        std::vector<glm::vec4> glm_vectors4 = {
                glm::vec4(),
                glm::vec4(19.562),
                glm::vec4(93.293, 17.1, -133, -82.001),
                glm::vec4(glm::vec4())
        };

        std::vector<float> numbers{4.2, -4.2};

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                Vector res = my_vectors2[i] / num;
                glm::vec2 glm_res = glm_vectors2[i] / num;
                compare_vectors<glm::vec2>(glm_res, res);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                Vector res = my_vectors3[i] / num;
                glm::vec3 glm_res = glm_vectors3[i] / num;
                compare_vectors<glm::vec3>(glm_res, res);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                Vector res = my_vectors4[i] / num;
                glm::vec4 glm_res = glm_vectors4[i] / num;
                compare_vectors<glm::vec4>(glm_res, res);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                my_vectors2[i] /= num;
                glm_vectors2[i] /= num;
                compare_vectors<glm::vec2>(glm_vectors2[i], my_vectors2[i]);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                my_vectors3[i] /= num;
                glm_vectors3[i] /= num;
                compare_vectors<glm::vec3>(glm_vectors3[i], my_vectors3[i]);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                my_vectors4[i] /= num;
                glm_vectors4[i] /= num;
                compare_vectors<glm::vec4>(glm_vectors4[i], my_vectors4[i]);
            }
        }

        REQUIRE_THROWS(my_vectors2[0] / 0);
        REQUIRE_THROWS(my_vectors3[0] / 0);
        REQUIRE_THROWS(my_vectors4[0] / 0);
        REQUIRE_THROWS(my_vectors2[0] /= 0);
        REQUIRE_THROWS(my_vectors3[0] /= 0);
        REQUIRE_THROWS(my_vectors4[0] /= 0);
    }

    SECTION("Equality and inequality of vectors") {
        std::vector<Vector> my_vectors = {
                Vector(2),
                Vector(2, -4.36),
                Vector{11.3, 4},
                Vector(3),
                Vector(3, 7.01),
                Vector{23.22, -13.09, 9},
                Vector(4),
                Vector(4, 19.562),
                Vector{93.293, 17.1, -133, -82.001}
        };

        for (int i = 0; i < my_vectors.size(); i++) {
            for (int j = 0; j < my_vectors.size(); j++) {
                if (i == j) {
                    REQUIRE(my_vectors[i] == my_vectors[j]);
                    continue;
                }

                REQUIRE(my_vectors[i] != my_vectors[j]);
            }
        }
    }

    SECTION("Length of vectors") {
        std::vector<Vector> my_vectors2 = {
                Vector(2),
                Vector(2, -4.36),
                Vector{11.3, 4},
                Vector(Vector(2))
        };

        std::vector<Vector> my_vectors3 = {
                Vector(3),
                Vector(3, 7.01),
                Vector{23.22, -13.09, 9},
                Vector(Vector(3))
        };

        std::vector<Vector> my_vectors4 = {
                Vector(4),
                Vector(4, 19.562),
                Vector{93.293, 17.1, -133, -82.001},
                Vector(Vector(4))
        };

        std::vector<glm::vec2> glm_vectors2 = {
                glm::vec2(),
                glm::vec2(-4.36),
                glm::vec2(11.3, 4),
                glm::vec2(glm::vec2())
        };

        std::vector<glm::vec3> glm_vectors3 = {
                glm::vec3(),
                glm::vec3(7.01),
                glm::vec3(23.22, -13.09, 9),
                glm::vec3(glm::vec3())
        };

        std::vector<glm::vec4> glm_vectors4 = {
                glm::vec4(),
                glm::vec4(19.562),
                glm::vec4(93.293, 17.1, -133, -82.001),
                glm::vec4(glm::vec4())
        };

        for (int i = 0; i < 4; ++i) {
            float res = my_vectors2[i].length();
            float glm_res = glm::length(glm_vectors2[i]);
            REQUIRE(std::abs(res - glm_res) < EPS);
        }

        for (int i = 0; i < 4; ++i) {
            float res = my_vectors3[i].length();
            float glm_res = glm::length(glm_vectors3[i]);
            REQUIRE(std::abs(res - glm_res) < EPS);
        }

        for (int i = 0; i < 4; ++i) {
            float res = my_vectors4[i].length();
            float glm_res = glm::length(glm_vectors4[i]);
            REQUIRE(std::abs(res - glm_res) < EPS);
        }

    }

    SECTION("Vector normalization") {
        std::vector<Vector> my_vectors2 = {
                Vector(2),
                Vector(2, -4.36),
                Vector{11.3, 4}
        };

        std::vector<Vector> my_vectors3 = {
                Vector(3),
                Vector(3, 7.01),
                Vector{23.22, -13.09, 9}
        };

        std::vector<Vector> my_vectors4 = {
                Vector(4),
                Vector(4, 19.562),
                Vector{93.293, 17.1, -133, -82.001}
        };

        std::vector<glm::vec2> glm_vectors2 = {
                glm::vec2(-4.36),
                glm::vec2(11.3, 4)
        };

        std::vector<glm::vec3> glm_vectors3 = {
                glm::vec3(7.01),
                glm::vec3(23.22, -13.09, 9)
        };

        std::vector<glm::vec4> glm_vectors4 = {
                glm::vec4(19.562),
                glm::vec4(93.293, 17.1, -133, -82.001)
        };

        for (int i = 1; i < 3; ++i) {
            Vector res = my_vectors2[i].normalize();
            glm::vec2 glm_res = glm::normalize(glm_vectors2[i - 1]);
            compare_vectors<glm::vec2>(glm_res, res);
        }

        for (int i = 1; i < 3; ++i) {
            Vector res = my_vectors3[i].normalize();
            glm::vec3 glm_res = glm::normalize(glm_vectors3[i - 1]);
            compare_vectors<glm::vec3>(glm_res, res);
        }

        for (int i = 1; i < 3; ++i) {
            Vector res = my_vectors4[i].normalize();
            glm::vec4 glm_res = glm::normalize(glm_vectors4[i - 1]);
            compare_vectors<glm::vec4>(glm_res, res);
        }

        REQUIRE_THROWS(my_vectors2[0].normalize());
        REQUIRE_THROWS(my_vectors3[0].normalize());
        REQUIRE_THROWS(my_vectors4[0].normalize());
    }

    SECTION("Output of vectors") {
        Vector vec1{1}, vec6{-1.123123, 2, 3.002, 4.363, 5, -6};

        std::ostringstream oss1;
        oss1 << vec1;
        REQUIRE(oss1.str() == "Vector[size=1]: [1]");

        std::ostringstream oss2;
        oss2 << vec6;
        REQUIRE(oss2.str() == "Vector[size=6]: [-1.12312, 2, 3.002, 4.363, 5, -6]");
    }
}

TEST_CASE("Matrix testing") {

    SECTION("Construction of matrix, getters") {
        auto **numbers2 = new float *[2];
        for (int i = 0; i < 2; ++i) {
            numbers2[i] = new float[2];
        }

        numbers2[0][0] = 34.7;
        numbers2[0][1] = -57.12;
        numbers2[1][0] = 39.272;
        numbers2[1][1] = -38;

        auto **numbers3 = new float *[3];
        for (int i = 0; i < 3; ++i) {
            numbers3[i] = new float[3];
        }

        numbers3[0][0] = -17;
        numbers3[0][1] = 39.272;
        numbers3[0][2] = -38.211;
        numbers3[1][0] = 74;
        numbers3[1][1] = 8.467;
        numbers3[1][2] = -2.53;
        numbers3[2][0] = -3.382;
        numbers3[2][1] = 34.72;
        numbers3[2][2] = 57.12;

        auto **numbers4 = new float *[4];
        for (int i = 0; i < 4; ++i) {
            numbers4[i] = new float[4];
        }

        numbers4[0][0] = 74.232;
        numbers4[0][1] = 8.467;
        numbers4[0][2] = -25.3;
        numbers4[0][3] = -83.382;
        numbers4[1][0] = 34.7;
        numbers4[1][1] = -57.12;
        numbers4[1][2] = 39.272;
        numbers4[1][3] = -38.5;
        numbers4[2][0] = -17;
        numbers4[2][1] = 39.272;
        numbers4[2][2] = -38;
        numbers4[2][3] = 74.3;
        numbers4[3][0] = 8.467;
        numbers4[3][1] = -253;
        numbers4[3][2] = -83.382;
        numbers4[3][3] = -34.7;

        std::vector<Matrix> my_matrix2{
                Matrix(2),
                Matrix(2, -4.36),
                Matrix{11.3, 4, 54, 9},
                Matrix(Matrix(2)),
                Matrix(2, numbers2)
        };

        std::vector<Matrix> my_matrix3{
                Matrix(3),
                Matrix(3, 7.01),
                Matrix{23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3},
                Matrix(Matrix(3)),
                Matrix(3, numbers3)
        };

        std::vector<Matrix> my_matrix4{
                Matrix(4),
                Matrix(4, 19.562),
                Matrix{93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8, 39.13, 48, 0.11, 23, 7},
                Matrix(Matrix(4)),
                Matrix(4, numbers4)
        };

        std::vector<glm::mat2> glm_matrix2 = {
                glm::mat2(),
                glm::mat2(-4.36, -4.36, -4.36, -4.36),
                glm::mat2(11.3, 4, 54, 9),
                glm::mat2(glm::mat2())
        };

        std::vector<glm::mat3> glm_matrix3 = {
                glm::mat3(),
                glm::mat3(7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01),
                glm::mat3(23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3),
                glm::mat3(glm::mat3())
        };

        std::vector<glm::mat4> glm_matrix4 = {
                glm::mat4(),
                glm::mat4(19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562),
                glm::mat4(93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8, 39.13, 48, 0.11, 23, 7),
                glm::mat4(glm::mat4())
        };

        for (int i = 0; i < 4; ++i) {
            REQUIRE(2 == my_matrix2[i].size());
            compare_matrix<glm::mat2>(glm_matrix2[i], my_matrix2[i]);
        }

        for (int i = 0; i < 4; ++i) {
            REQUIRE(3 == my_matrix3[i].size());
            compare_matrix<glm::mat3>(glm_matrix3[i], my_matrix3[i]);
        }

        for (int i = 0; i < 4; ++i) {
            REQUIRE(4 == my_matrix4[i].size());
            compare_matrix<glm::mat4>(glm_matrix4[i], my_matrix4[i]);
        }

        for (int i = 0; i < 2; ++i) {
            delete[] numbers2[i];
        }
        delete[] numbers2;

        for (int i = 0; i < 3; ++i) {
            delete[] numbers3[i];
        }
        delete[] numbers3;

        for (int i = 0; i < 4; ++i) {
            delete[] numbers4[i];
        }
        delete[] numbers4;

        REQUIRE_THROWS(Matrix{1, 2, 3, 3, 3});
    }

    SECTION("Copy of matrix with assignment operator") {
        std::vector<Matrix> my_matrix = {
                Matrix(2),
                Matrix(2, -4.36),
                Matrix{11.3, 4, 54, 9},
                Matrix(3),
                Matrix(3, 7.01),
                Matrix{23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3},
                Matrix(4),
                Matrix(4, 19.562),
                Matrix{93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8, 39.13, 48, 0.11, 23, 7}
        };

        for (auto mat: my_matrix) {
            Matrix mat_copy(1);
            mat_copy = mat;
            REQUIRE(mat_copy == mat);

            mat = mat;
            REQUIRE(mat == mat);
        }
    }

    SECTION("Matrix addition") {
        std::vector<Matrix> my_matrix2 = {
                Matrix(2),
                Matrix(2, -4.36),
                Matrix{11.3, 4, 54, 9},
                Matrix(Matrix(2))
        };

        std::vector<Matrix> my_matrix3 = {
                Matrix(3),
                Matrix(3, 7.01),
                Matrix{23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3},
                Matrix(Matrix(3))
        };

        std::vector<Matrix> my_matrix4 = {
                Matrix(4),
                Matrix(4, 19.562),
                Matrix{93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8, 39.13, 48, 0.11, 23, 7},
                Matrix(Matrix(4))
        };

        std::vector<glm::mat2> glm_matrix2 = {
                glm::mat2(),
                glm::mat2(-4.36, -4.36, -4.36, -4.36),
                glm::mat2(11.3, 4, 54, 9),
                glm::mat2(glm::mat2())
        };

        std::vector<glm::mat3> glm_matrix3 = {
                glm::mat3(),
                glm::mat3(7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01),
                glm::mat3(23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3),
                glm::mat3(glm::mat3())
        };

        std::vector<glm::mat4> glm_matrix4 = {
                glm::mat4(),
                glm::mat4(19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562),
                glm::mat4(93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8, 39.13, 48, 0.11, 23, 7),
                glm::mat4(glm::mat4())
        };

        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                Matrix res = my_matrix2[i] + my_matrix2[j];
                glm::mat2 glm_res = glm_matrix2[i] + glm_matrix2[j];
                compare_matrix<glm::mat2>(glm_res, res);
            }
        }

        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                Matrix res = my_matrix3[i] + my_matrix3[j];
                glm::mat3 glm_res = glm_matrix3[i] + glm_matrix3[j];
                compare_matrix<glm::mat3>(glm_res, res);
            }
        }

        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                Matrix res = my_matrix4[i] + my_matrix4[j];
                glm::mat4 glm_res = glm_matrix4[i] + glm_matrix4[j];
                compare_matrix<glm::mat4>(glm_res, res);
            }
        }

        for (int i = 0; i < 3; ++i) {
            my_matrix2[i] += my_matrix2[i + 1];
            glm_matrix2[i] += glm_matrix2[i + 1];
            compare_matrix<glm::mat2>(glm_matrix2[i], my_matrix2[i]);
        }

        for (int i = 0; i < 3; ++i) {
            my_matrix3[i] += my_matrix3[i + 1];
            glm_matrix3[i] += glm_matrix3[i + 1];
            compare_matrix<glm::mat3>(glm_matrix3[i], my_matrix3[i]);
        }

        for (int i = 0; i < 3; ++i) {
            my_matrix4[i] += my_matrix4[i + 1];
            glm_matrix4[i] += glm_matrix4[i + 1];
            compare_matrix<glm::mat4>(glm_matrix4[i], my_matrix4[i]);
        }

        REQUIRE_THROWS(my_matrix2[0] + my_matrix3[0]);
    }

    SECTION("Matrix and float addition") {
        std::vector<Matrix> my_matrix2 = {
                Matrix(2),
                Matrix(2, -4.36),
                Matrix{11.3, 4, 54, 9},
                Matrix(Matrix(2))
        };

        std::vector<Matrix> my_matrix3 = {
                Matrix(3),
                Matrix(3, 7.01),
                Matrix{23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3},
                Matrix(Matrix(3))
        };

        std::vector<Matrix> my_matrix4 = {
                Matrix(4),
                Matrix(4, 19.562),
                Matrix{93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8, 39.13, 48, 0.11, 23, 7},
                Matrix(Matrix(4))
        };

        std::vector<glm::mat2> glm_matrix2 = {
                glm::mat2(),
                glm::mat2(-4.36, -4.36, -4.36, -4.36),
                glm::mat2(11.3, 4, 54, 9),
                glm::mat2(glm::mat2())
        };

        std::vector<glm::mat3> glm_matrix3 = {
                glm::mat3(),
                glm::mat3(7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01),
                glm::mat3(23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3),
                glm::mat3(glm::mat3())
        };

        std::vector<glm::mat4> glm_matrix4 = {
                glm::mat4(),
                glm::mat4(19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562),
                glm::mat4(93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8, 39.13, 48, 0.11, 23, 7),
                glm::mat4(glm::mat4())
        };

        std::vector<float> numbers{4.2, -4.2, 0.0};

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                Matrix res = my_matrix2[i] + num;
                glm::mat2 glm_res = glm_matrix2[i] + num;
                compare_matrix<glm::mat2>(glm_res, res);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                Matrix res = my_matrix3[i] + num;
                glm::mat3 glm_res = glm_matrix3[i] + num;
                compare_matrix<glm::mat3>(glm_res, res);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                Matrix res = my_matrix4[i] + num;
                glm::mat4 glm_res = glm_matrix4[i] + num;
                compare_matrix<glm::mat4>(glm_res, res);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                my_matrix2[i] += num;
                glm_matrix2[i] += num;
                compare_matrix<glm::mat2>(glm_matrix2[i], my_matrix2[i]);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                my_matrix3[i] += num;
                glm_matrix3[i] += num;
                compare_matrix<glm::mat3>(glm_matrix3[i], my_matrix3[i]);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                my_matrix4[i] += num;
                glm_matrix4[i] += num;
                compare_matrix<glm::mat4>(glm_matrix4[i], my_matrix4[i]);
            }
        }
    }

    SECTION("Matrix subtraction") {
        std::vector<Matrix> my_matrix2 = {
                Matrix(2),
                Matrix(2, -4.36),
                Matrix{11.3, 4, 54, 9},
                Matrix(Matrix(2))
        };

        std::vector<Matrix> my_matrix3 = {
                Matrix(3),
                Matrix(3, 7.01),
                Matrix{23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3},
                Matrix(Matrix(3))
        };

        std::vector<Matrix> my_matrix4 = {
                Matrix(4),
                Matrix(4, 19.562),
                Matrix{93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8, 39.13, 48, 0.11, 23, 7},
                Matrix(Matrix(4))
        };

        std::vector<glm::mat2> glm_matrix2 = {
                glm::mat2(),
                glm::mat2(-4.36, -4.36, -4.36, -4.36),
                glm::mat2(11.3, 4, 54, 9),
                glm::mat2(glm::mat2())
        };

        std::vector<glm::mat3> glm_matrix3 = {
                glm::mat3(),
                glm::mat3(7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01),
                glm::mat3(23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3),
                glm::mat3(glm::mat3())
        };

        std::vector<glm::mat4> glm_matrix4 = {
                glm::mat4(),
                glm::mat4(19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562),
                glm::mat4(93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8, 39.13, 48, 0.11, 23, 7),
                glm::mat4(glm::mat4())
        };

        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                Matrix res = my_matrix2[i] - my_matrix2[j];
                glm::mat2 glm_res = glm_matrix2[i] - glm_matrix2[j];
                compare_matrix<glm::mat2>(glm_res, res);
            }
        }

        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                Matrix res = my_matrix3[i] - my_matrix3[j];
                glm::mat3 glm_res = glm_matrix3[i] - glm_matrix3[j];
                compare_matrix<glm::mat3>(glm_res, res);
            }
        }

        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                Matrix res = my_matrix4[i] - my_matrix4[j];
                glm::mat4 glm_res = glm_matrix4[i] - glm_matrix4[j];
                compare_matrix<glm::mat4>(glm_res, res);
            }
        }

        for (int i = 0; i < 3; ++i) {
            my_matrix2[i] -= my_matrix2[i + 1];
            glm_matrix2[i] -= glm_matrix2[i + 1];
            compare_matrix<glm::mat2>(glm_matrix2[i], my_matrix2[i]);
        }

        for (int i = 0; i < 3; ++i) {
            my_matrix3[i] -= my_matrix3[i + 1];
            glm_matrix3[i] -= glm_matrix3[i + 1];
            compare_matrix<glm::mat3>(glm_matrix3[i], my_matrix3[i]);
        }

        for (int i = 0; i < 3; ++i) {
            my_matrix4[i] -= my_matrix4[i + 1];
            glm_matrix4[i] -= glm_matrix4[i + 1];
            compare_matrix<glm::mat4>(glm_matrix4[i], my_matrix4[i]);
        }

        REQUIRE_THROWS(my_matrix2[0] - my_matrix3[0]);
    }

    SECTION("Matrix and float subtraction") {
        std::vector<Matrix> my_matrix2 = {
                Matrix(2),
                Matrix(2, -4.36),
                Matrix{11.3, 4, 54, 9},
                Matrix(Matrix(2))
        };

        std::vector<Matrix> my_matrix3 = {
                Matrix(3),
                Matrix(3, 7.01),
                Matrix{23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3},
                Matrix(Matrix(3))
        };

        std::vector<Matrix> my_matrix4 = {
                Matrix(4),
                Matrix(4, 19.562),
                Matrix{93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8, 39.13, 48, 0.11, 23, 7},
                Matrix(Matrix(4))
        };

        std::vector<glm::mat2> glm_matrix2 = {
                glm::mat2(),
                glm::mat2(-4.36, -4.36, -4.36, -4.36),
                glm::mat2(11.3, 4, 54, 9),
                glm::mat2(glm::mat2())
        };

        std::vector<glm::mat3> glm_matrix3 = {
                glm::mat3(),
                glm::mat3(7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01),
                glm::mat3(23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3),
                glm::mat3(glm::mat3())
        };

        std::vector<glm::mat4> glm_matrix4 = {
                glm::mat4(),
                glm::mat4(19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562),
                glm::mat4(93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8, 39.13, 48, 0.11, 23, 7),
                glm::mat4(glm::mat4())
        };

        std::vector<float> numbers{4.2, -4.2, 0.0};

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                Matrix res = my_matrix2[i] - num;
                glm::mat2 glm_res = glm_matrix2[i] - num;
                compare_matrix<glm::mat2>(glm_res, res);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                Matrix res = my_matrix3[i] - num;
                glm::mat3 glm_res = glm_matrix3[i] - num;
                compare_matrix<glm::mat3>(glm_res, res);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                Matrix res = my_matrix4[i] - num;
                glm::mat4 glm_res = glm_matrix4[i] - num;
                compare_matrix<glm::mat4>(glm_res, res);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                my_matrix2[i] -= num;
                glm_matrix2[i] -= num;
                compare_matrix<glm::mat2>(glm_matrix2[i], my_matrix2[i]);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                my_matrix3[i] -= num;
                glm_matrix3[i] -= num;
                compare_matrix<glm::mat3>(glm_matrix3[i], my_matrix3[i]);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                my_matrix4[i] -= num;
                glm_matrix4[i] -= num;
                compare_matrix<glm::mat4>(glm_matrix4[i], my_matrix4[i]);
            }
        }
    }

    SECTION("Multiply matrix by float") {
        std::vector<Matrix> my_matrix2 = {
                Matrix(2),
                Matrix(2, -4.36),
                Matrix{11.3, 4, 54, 9},
                Matrix(Matrix(2))
        };

        std::vector<Matrix> my_matrix3 = {
                Matrix(3),
                Matrix(3, 7.01),
                Matrix{23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3},
                Matrix(Matrix(3))
        };

        std::vector<Matrix> my_matrix4 = {
                Matrix(4),
                Matrix(4, 19.562),
                Matrix{93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8, 39.13, 48, 0.11, 23, 7},
                Matrix(Matrix(4))
        };

        std::vector<glm::mat2> glm_matrix2 = {
                glm::mat2(),
                glm::mat2(-4.36, -4.36, -4.36, -4.36),
                glm::mat2(11.3, 4, 54, 9),
                glm::mat2(glm::mat2())
        };

        std::vector<glm::mat3> glm_matrix3 = {
                glm::mat3(),
                glm::mat3(7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01),
                glm::mat3(23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3),
                glm::mat3(glm::mat3())
        };

        std::vector<glm::mat4> glm_matrix4 = {
                glm::mat4(),
                glm::mat4(19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562),
                glm::mat4(93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8, 39.13, 48, 0.11, 23, 7),
                glm::mat4(glm::mat4())
        };

        std::vector<float> numbers{4.2, -4.2, 0.0};

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                Matrix res = my_matrix2[i] * num;
                glm::mat2 glm_res = glm_matrix2[i] * num;
                compare_matrix<glm::mat2>(glm_res, res);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                Matrix res = my_matrix3[i] * num;
                glm::mat3 glm_res = glm_matrix3[i] * num;
                compare_matrix<glm::mat3>(glm_res, res);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                Matrix res = my_matrix4[i] * num;
                glm::mat4 glm_res = glm_matrix4[i] * num;
                compare_matrix<glm::mat4>(glm_res, res);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                my_matrix2[i] *= num;
                glm_matrix2[i] *= num;
                compare_matrix<glm::mat2>(glm_matrix2[i], my_matrix2[i]);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                my_matrix3[i] *= num;
                glm_matrix3[i] *= num;
                compare_matrix<glm::mat3>(glm_matrix3[i], my_matrix3[i]);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                my_matrix4[i] *= num;
                glm_matrix4[i] *= num;
                compare_matrix<glm::mat4>(glm_matrix4[i], my_matrix4[i]);
            }
        }
    }

    SECTION("Matrix product") {
        std::vector<Matrix> my_matrix2 = {
                Matrix(2),
                Matrix(2, -4.36),
                Matrix{11.3, 4, 54, 9},
                Matrix(Matrix(2))
        };

        std::vector<Matrix> my_matrix3 = {
                Matrix(3),
                Matrix(3, 7.01),
                Matrix{23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3},
                Matrix(Matrix(3))
        };

        std::vector<Matrix> my_matrix4 = {
                Matrix(4),
                Matrix(4, 19.562),
                Matrix{93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8, 39.13, 48, 0.11, 23, 7},
                Matrix(Matrix(4))
        };

        std::vector<glm::mat2> glm_matrix2 = {
                glm::mat2(),
                glm::mat2(-4.36, -4.36, -4.36, -4.36),
                glm::mat2(11.3, 4, 54, 9),
                glm::mat2(glm::mat2())
        };

        std::vector<glm::mat3> glm_matrix3 = {
                glm::mat3(),
                glm::mat3(7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01),
                glm::mat3(23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3),
                glm::mat3(glm::mat3())
        };

        std::vector<glm::mat4> glm_matrix4 = {
                glm::mat4(),
                glm::mat4(19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562),
                glm::mat4(93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8, 39.13, 48, 0.11, 23, 7),
                glm::mat4(glm::mat4())
        };

        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                Matrix res = my_matrix2[i] * my_matrix2[j];
                glm::mat2 glm_res = glm_matrix2[j] * glm_matrix2[i];
                compare_matrix<glm::mat2>(glm_res, res);
            }
        }

        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                Matrix res = my_matrix3[i] * my_matrix3[j];
                glm::mat3 glm_res = glm_matrix3[j] * glm_matrix3[i];
                compare_matrix<glm::mat3>(glm_res, res);
            }
        }

        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                Matrix res = my_matrix4[i] * my_matrix4[j];
                glm::mat4 glm_res = glm_matrix4[j] * glm_matrix4[i];
                compare_matrix<glm::mat4>(glm_res, res);
            }
        }

        for (int i = 0; i < 3; ++i) {
            my_matrix2[i] *= my_matrix2[i + 1];
            glm::mat2 temp = glm_matrix2[i + 1] * glm_matrix2[i];
            glm_matrix2[i] = temp;
            compare_matrix<glm::mat2>(glm_matrix2[i], my_matrix2[i]);
        }

        for (int i = 0; i < 3; ++i) {
            my_matrix3[i] *= my_matrix3[i + 1];
            glm::mat3 temp = glm_matrix3[i + 1] * glm_matrix3[i];
            glm_matrix3[i] = temp;
            compare_matrix<glm::mat3>(glm_matrix3[i], my_matrix3[i]);
        }

        for (int i = 0; i < 3; ++i) {
            my_matrix4[i] *= my_matrix4[i + 1];
            glm::mat4 temp = glm_matrix4[i + 1] * glm_matrix4[i];
            glm_matrix4[i] = temp;
            compare_matrix<glm::mat4>(glm_matrix4[i], my_matrix4[i]);
        }

        REQUIRE_THROWS(my_matrix2[0] * my_matrix3[0]);
    }

    SECTION("Multiply matrix by vector") {
        std::vector<Matrix> my_matrix2 = {
                Matrix(2),
                Matrix(2, -4.36),
                Matrix{11.3, 4, 54, 9},
                Matrix(Matrix(2))
        };

        std::vector<Matrix> my_matrix3 = {
                Matrix(3),
                Matrix(3, 7.01),
                Matrix{23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3},
                Matrix(Matrix(3))
        };

        std::vector<Matrix> my_matrix4 = {
                Matrix(4),
                Matrix(4, 19.562),
                Matrix{93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8, 39.13, 48, 0.11, 23, 7},
                Matrix(Matrix(4))
        };

        std::vector<glm::mat2> glm_matrix2 = {
                glm::mat2(),
                glm::mat2(-4.36, -4.36, -4.36, -4.36),
                glm::mat2(11.3, 4, 54, 9),
                glm::mat2(glm::mat2())
        };

        std::vector<glm::mat3> glm_matrix3 = {
                glm::mat3(),
                glm::mat3(7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01),
                glm::mat3(23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3),
                glm::mat3(glm::mat3())
        };

        std::vector<glm::mat4> glm_matrix4 = {
                glm::mat4(),
                glm::mat4(19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562),
                glm::mat4(93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8, 39.13, 48, 0.11, 23, 7),
                glm::mat4(glm::mat4())
        };

        std::vector<Vector> my_vectors2 = {
                Vector(2),
                Vector(2, -4.36),
                Vector{11.3, 4}
        };

        std::vector<Vector> my_vectors3 = {
                Vector(3),
                Vector(3, 7.01),
                Vector{23.22, -13.09, 9}
        };

        std::vector<Vector> my_vectors4 = {
                Vector(4),
                Vector(4, 19.562),
                Vector{93.293, 17.1, -133, -82.001}
        };

        std::vector<glm::vec2> glm_vectors2 = {
                glm::vec2(),
                glm::vec2(-4.36),
                glm::vec2(11.3, 4)
        };

        std::vector<glm::vec3> glm_vectors3 = {
                glm::vec3(),
                glm::vec3(7.01),
                glm::vec3(23.22, -13.09, 9)
        };

        std::vector<glm::vec4> glm_vectors4 = {
                glm::vec4(),
                glm::vec4(19.562),
                glm::vec4(93.293, 17.1, -133, -82.001)
        };

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 3; ++j) {
                Vector res = my_matrix2[i] * my_vectors2[j];
                glm::vec2 glm_res = glm_vectors2[j] * glm_matrix2[i];
                compare_vectors(glm_res, res);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 3; ++j) {
                Vector res = my_matrix3[i] * my_vectors3[j];
                glm::vec3 glm_res = glm_vectors3[j] * glm_matrix3[i];
                compare_vectors(glm_res, res);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 3; ++j) {
                Vector res = my_matrix4[i] * my_vectors4[j];
                glm::vec4 glm_res = glm_vectors4[j] * glm_matrix4[i];
                compare_vectors(glm_res, res);
            }
        }

        REQUIRE_THROWS(my_matrix2[0] * my_vectors4[0]);
    }

    SECTION("Divide matrix by float") {
        std::vector<Matrix> my_matrix2 = {
                Matrix(2),
                Matrix(2, -4.36),
                Matrix{11.3, 4, 54, 9},
                Matrix(Matrix(2))
        };

        std::vector<Matrix> my_matrix3 = {
                Matrix(3),
                Matrix(3, 7.01),
                Matrix{23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3},
                Matrix(Matrix(3))
        };

        std::vector<Matrix> my_matrix4 = {
                Matrix(4),
                Matrix(4, 19.562),
                Matrix{93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8, 39.13, 48, 0.11, 23, 7},
                Matrix(Matrix(4))
        };

        std::vector<glm::mat2> glm_matrix2 = {
                glm::mat2(),
                glm::mat2(-4.36, -4.36, -4.36, -4.36),
                glm::mat2(11.3, 4, 54, 9),
                glm::mat2(glm::mat2())
        };

        std::vector<glm::mat3> glm_matrix3 = {
                glm::mat3(),
                glm::mat3(7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01),
                glm::mat3(23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3),
                glm::mat3(glm::mat3())
        };

        std::vector<glm::mat4> glm_matrix4 = {
                glm::mat4(),
                glm::mat4(19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562),
                glm::mat4(93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8, 39.13, 48, 0.11, 23, 7),
                glm::mat4(glm::mat4())
        };

        std::vector<float> numbers{4.2, -4.2};

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                Matrix res = my_matrix2[i] / num;
                glm::mat2 glm_res = glm_matrix2[i] / num;
                compare_matrix<glm::mat2>(glm_res, res);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                Matrix res = my_matrix3[i] / num;
                glm::mat3 glm_res = glm_matrix3[i] / num;
                compare_matrix<glm::mat3>(glm_res, res);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                Matrix res = my_matrix4[i] / num;
                glm::mat4 glm_res = glm_matrix4[i] / num;
                compare_matrix<glm::mat4>(glm_res, res);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                my_matrix2[i] /= num;
                glm_matrix2[i] /= num;
                compare_matrix<glm::mat2>(glm_matrix2[i], my_matrix2[i]);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                my_matrix3[i] /= num;
                glm_matrix3[i] /= num;
                compare_matrix<glm::mat3>(glm_matrix3[i], my_matrix3[i]);
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (auto num: numbers) {
                my_matrix4[i] /= num;
                glm_matrix4[i] /= num;
                compare_matrix<glm::mat4>(glm_matrix4[i], my_matrix4[i]);
            }
        }

        REQUIRE_THROWS(my_matrix2[0] / 0);
        REQUIRE_THROWS(my_matrix3[0] / 0);
        REQUIRE_THROWS(my_matrix4[0] / 0);
        REQUIRE_THROWS(my_matrix2[0] /= 0);
        REQUIRE_THROWS(my_matrix3[0] /= 0);
        REQUIRE_THROWS(my_matrix4[0] /= 0);
    }

    SECTION("Equality and inequality of matrix") {
        std::vector<Matrix> my_matrix = {
                Matrix(2),
                Matrix(2, -4.36),
                Matrix{11.3, 4, 54, 9},
                Matrix(3),
                Matrix(3, 7.01),
                Matrix{23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3},
                Matrix(4),
                Matrix(4, 19.562),
                Matrix{93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8, 39.13, 48, 0.11, 23, 7},
        };

        for (int i = 0; i < my_matrix.size(); i++) {
            for (int j = 0; j < my_matrix.size(); j++) {
                if (i == j) {
                    REQUIRE(my_matrix[i] == my_matrix[j]);
                    continue;
                }

                REQUIRE(my_matrix[i] != my_matrix[j]);
            }
        }
    }

    SECTION("Generation identity matrix") {
        Matrix my_mat2 = Matrix::identity_matrix(2);
        Matrix my_mat3 = Matrix::identity_matrix(3);
        Matrix my_mat4 = Matrix::identity_matrix(4);

        glm::mat2 glm_mat2 = glm::mat2(1);
        glm::mat3 glm_mat3 = glm::mat3(1);
        glm::mat4 glm_mat4 = glm::mat4(1);

        compare_matrix(glm_mat2, my_mat2);
        compare_matrix(glm_mat3, my_mat3);
        compare_matrix(glm_mat4, my_mat4);
    }

    SECTION("Generation transposed matrix") {
        std::vector<Matrix> my_matrix2 = {
                Matrix(2),
                Matrix(2, -4.36),
                Matrix{11.3, 4, 54, 9},
                Matrix(Matrix(2))
        };

        std::vector<Matrix> my_matrix3 = {
                Matrix(3),
                Matrix(3, 7.01),
                Matrix{23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3},
                Matrix(Matrix(3))
        };

        std::vector<Matrix> my_matrix4 = {
                Matrix(4),
                Matrix(4, 19.562),
                Matrix{93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8, 39.13, 48, 0.11, 23, 7},
                Matrix(Matrix(4))
        };

        std::vector<glm::mat2> glm_matrix2 = {
                glm::mat2(),
                glm::mat2(-4.36, -4.36, -4.36, -4.36),
                glm::mat2(11.3, 4, 54, 9),
                glm::mat2(glm::mat2())
        };

        std::vector<glm::mat3> glm_matrix3 = {
                glm::mat3(),
                glm::mat3(7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01),
                glm::mat3(23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3),
                glm::mat3(glm::mat3())
        };

        std::vector<glm::mat4> glm_matrix4 = {
                glm::mat4(),
                glm::mat4(19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562),
                glm::mat4(93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8, 39.13, 48, 0.11, 23, 7),
                glm::mat4(glm::mat4())
        };

        for (int i = 0; i < 4; ++i) {
            Matrix res = my_matrix2[i].transposed();
            glm::mat2 glm_res = glm::transpose(glm_matrix2[i]);
            compare_matrix<glm::mat2>(glm_res, res);
        }

        for (int i = 0; i < 4; ++i) {
            Matrix res = my_matrix3[i].transposed();
            glm::mat3 glm_res = glm::transpose(glm_matrix3[i]);
            compare_matrix<glm::mat3>(glm_res, res);
        }

        for (int i = 0; i < 4; ++i) {
            Matrix res = my_matrix4[i].transposed();
            glm::mat4 glm_res = glm::transpose(glm_matrix4[i]);
            compare_matrix<glm::mat4>(glm_res, res);
        }
    }

    SECTION("Calculation matrix determinant") {
        std::vector<Matrix> my_matrix2 = {
                Matrix(2),
                Matrix(2, -4.36),
                Matrix{11.3, 4, 54, 9},
                Matrix(Matrix(2))
        };

        std::vector<Matrix> my_matrix3 = {
                Matrix(3),
                Matrix(3, 7.01),
                Matrix{23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3},
                Matrix(Matrix(3))
        };

        std::vector<Matrix> my_matrix4 = {
                Matrix(4),
                Matrix(4, 19.562),
                Matrix{93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8, 39.13, 48, 0.11, 23, 7},
                Matrix(Matrix(4))
        };

        std::vector<glm::mat2> glm_matrix2 = {
                glm::mat2(),
                glm::mat2(-4.36, -4.36, -4.36, -4.36),
                glm::mat2(11.3, 4, 54, 9),
                glm::mat2(glm::mat2())
        };

        std::vector<glm::mat3> glm_matrix3 = {
                glm::mat3(),
                glm::mat3(7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01, 7.01),
                glm::mat3(23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3),
                glm::mat3(glm::mat3())
        };

        std::vector<glm::mat4> glm_matrix4 = {
                glm::mat4(),
                glm::mat4(19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562, 19.562),
                glm::mat4(93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8, 39.13, 48, 0.11, 23, 7),
                glm::mat4(glm::mat4())
        };

        for (int i = 0; i < 4; ++i) {
            float res = my_matrix2[i].determinant();
            float glm_res = glm::determinant(glm_matrix2[i]);
            REQUIRE((glm_res - res) < EPS);
        }

        for (int i = 0; i < 4; ++i) {
            float res = my_matrix3[i].determinant();
            float glm_res = glm::determinant(glm_matrix3[i]);
            REQUIRE((glm_res - res) < DET_EPS);
        }

        for (int i = 0; i < 4; ++i) {
            float res = my_matrix4[i].determinant();
            float glm_res = glm::determinant(glm_matrix4[i]);
            REQUIRE((glm_res - res) < DET_EPS);
        }

        Matrix mat = Matrix(1, 67);
        float det = mat.determinant();
        REQUIRE((det - 67) < DET_EPS);
    }

    SECTION("Calculation inverse matrix") {
        std::vector<Matrix> my_matrix2 = {
                Matrix{11.3, 4, 54, 9},
                Matrix{72, 8, -3, -39},
                Matrix{-82.001, 93, -39.2, -24}
        };

        std::vector<Matrix> my_matrix3 = {
                Matrix{23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3},
                Matrix{-29.3, -42.3, 84.231, 8, 24, 8.33, 4, 12, -48},
                Matrix{93, -39.2, -24, -38.34, 323, 0, 0, 82, -9}
        };

        std::vector<Matrix> my_matrix4 = {
                Matrix{93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8, 39.13, 48, 0.11, 23, 7},
                Matrix{-2, -39.3, 17.117, 3, -5, -8, 84, 23.13, -4.3241, 11.3, 4, 54, 9, 0, 72, 1},
                Matrix{Matrix::identity_matrix(4)}
        };

        std::vector<glm::mat2> glm_matrix2 = {
                glm::mat2(11.3, 4, 54, 9),
                glm::mat2(72, 8, -3, -39),
                glm::mat2(-82.001, 93, -39.2, -24)
        };

        std::vector<glm::mat3> glm_matrix3 = {
                glm::mat3(23.22, -13.09, 9, 48, -3.34, 84, 45.73, -46.3, 3),
                glm::mat3(-29.3, -42.3, 84.231, 8, 24, 8.33, 4, 12, -48),
                glm::mat3(93, -39.2, -24, -38.34, 323, 0, 0, 82, -9)
        };

        std::vector<glm::mat4> glm_matrix4 = {
                glm::mat4(93.293, 17.1, -133, -82.001, 93, -39.2, -24, -38.34, 323, 4, 8, 39.13, 48, 0.11, 23, 7),
                glm::mat4(-2, -39.3, 17.117, 3, -5, -8, 84, 23.13, -4.3241, 11.3, 4, 54, 9, 0, 72, 1),
                glm::mat4(1)
        };

        for (int i = 0; i < 3; ++i) {
            Matrix res = my_matrix2[i].inverse();
            glm::mat2 glm_res = glm::inverse(glm_matrix2[i]);
            compare_matrix(glm_res, res);
        }

        for (int i = 0; i < 3; ++i) {
            Matrix res = my_matrix3[i].inverse();
            glm::mat3 glm_res = glm::inverse(glm_matrix3[i]);
            compare_matrix(glm_res, res);
        }

        for (int i = 0; i < 3; ++i) {
            Matrix res = my_matrix4[i].inverse();
            glm::mat4 glm_res = glm::inverse(glm_matrix4[i]);
            compare_matrix(glm_res, res);
        }

        REQUIRE_THROWS(Matrix(5).inverse());
    }

    SECTION("Generation transform matrix") {
        std::vector<Vector> my_vectors = {
                Vector(3, 7.01),
                Vector(3, -2),
                Vector{23.22, -13.09, 9},
                Vector{3, 36, -425.1},
                Vector{9.34, 421, -24}
        };

        std::vector<glm::vec3> glm_vectors = {
                glm::vec3(7.01, 7.01, 7.01),
                glm::vec3(-2, -2, -2),
                glm::vec3(23.22, -13.09, 9),
                glm::vec3(3, 36, -425.1),
                glm::vec3(9.34, 421, -24)
        };

        for (int i = 0; i < 5; ++i) {
            Matrix res = Matrix::transform(my_vectors[i]);
            glm::mat4 glm_res = glm::transpose(glm::translate(glm::mat4(1), glm_vectors[i]));
            compare_matrix(glm_res, res);
        }

        REQUIRE_THROWS(Matrix::transform(Vector(2)));
        REQUIRE_THROWS(Matrix::transform(Vector(4)));
    }

    SECTION("Generation scale matrix") {
        std::vector<Vector> my_vectors = {
            Vector(3, 7.01),
            Vector(3, -2),
            Vector{23.22, -13.09, 9},
            Vector{3, 36, -425.1},
            Vector{9.34, 421, -24}
        };

        std::vector<glm::vec3> glm_vectors = {
                glm::vec3(7.01, 7.01, 7.01),
                glm::vec3(-2, -2, -2),
                glm::vec3(23.22, -13.09, 9),
                glm::vec3(3, 36, -425.1),
                glm::vec3(9.34, 421, -24)
        };

        for (int i = 0; i < 5; ++i) {
            Matrix res = Matrix::scale(my_vectors[i]);
            glm::mat4 glm_res = glm::scale(glm::mat4(1), glm_vectors[i]);
            compare_matrix(glm_res, res);
        }

        REQUIRE_THROWS(Matrix::scale(Vector(2)));
        REQUIRE_THROWS(Matrix::scale(Vector(4)));
    }

//    SECTION("Generation rotate matrix") {
//        std::vector<float> alpha_vec = {0, 30, 45, 90, -30, -45, -90};
//        std::vector<float> beta_vec = {0, 30, 45, 90, -30, -45, -90};
//        std::vector<float> gamma_vec = {0, 30, 45, 90, -30, -45, -90};
//
//        for (int i = 0; i < 5; ++i) {
//            Matrix res = Matrix::rotate(alpha_vec[i], beta_vec[i], gamma_vec[i]);
//            glm::mat4 glm_res =
//            compare_matrix(glm_res, res);
//        }
//    }

    SECTION("Generation lookAt matrix") {
        std::vector<Vector> my_vectors = {
                Vector(3, 7.01),
                Vector(3, -2),
                Vector{23.22, -13.09, 9},
                Vector{3, 36, -425.1},
                Vector{9.34, 421, -24}
        };

        std::vector<glm::vec3> glm_vectors = {
                glm::vec3(7.01, 7.01, 7.01),
                glm::vec3(-2, -2, -2),
                glm::vec3(23.22, -13.09, 9),
                glm::vec3(3, 36, -425.1),
                glm::vec3(9.34, 421, -24)
        };

        for (int i = 0; i < 5; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                Matrix res = Matrix::look_at(my_vectors[i], my_vectors[j], Vector{0, 0, 1});
                glm::mat4 glm_res = glm::lookAt(glm_vectors[i], glm_vectors[j], glm::vec3(0, 0, 1));
                compare_matrix(glm_res, res);
            }
        }
    }

    SECTION("Generation perspective matrix") {
        std::vector<float> floats = {-53, 1.1414, 23, -4, 7.4, 9, 19.14, 34, 149, 4, -33.2, -34.4, 48.34, 50.002, -59.435, 48.1, 3, 48};

        for (int i = 0; i < 16; ++i) {
            for (int j = i + 1; j < 17; ++j) {
                Matrix res = Matrix::perspective(floats[i], floats[j], floats[i + 1], floats[j + 1]);
                glm::mat4 glm_res = glm::perspective(floats[i], floats[j], floats[i + 1], floats[j + 1]);
                compare_matrix(glm_res, res);
            }
        }
    }

    SECTION("Generation ortho matrix") {
        std::vector<float> floats = {-53, 1.1414, 23, -4, 7.4, 9, 19.14, 34, 149, 4, -33.2, -34.4};

        Matrix res = Matrix::ortho(floats[0], floats[1], floats[2], floats[3], floats[4], floats[5]);
        glm::mat4 glm_res = glm::transpose(glm::ortho(floats[0], floats[1], floats[2], floats[3], floats[4], floats[5]));
        compare_matrix(glm_res, res);

        Matrix res2 = Matrix::ortho(floats[6], floats[7], floats[8], floats[9], floats[10], floats[11]);
        glm::mat4 glm_res2 = glm::transpose(glm::ortho(floats[6], floats[7], floats[8], floats[9], floats[10], floats[11]));
        compare_matrix(glm_res2, res2);
    }

    SECTION("Output of matrix") {
        Matrix mat1{1}, mat3{-1.12, 2, 3.002, 4.363, 5, -6, 95, 0.001, -39};

        std::ostringstream oss1;
        oss1 << mat1;
        REQUIRE(oss1.str() == "Matrix[size=1x1]: [[1]]");

        std::ostringstream oss2;
        oss2 << mat3;
        REQUIRE(oss2.str() == "Matrix[size=3x3]: [[-1.12, 2, 3.002], [4.363, 5, -6], [95, 0.001, -39]]");
    }
}