#define CATCH_CONFIG_MAIN

#define EPS 10e-8

#include "../external/catch.hpp"
#include "../Matrix.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

template<typename T>
void compare_vectors(T glm_vector, Vector my_vec) {
    for (int i = 0; i < my_vec.size(); ++i) {
        REQUIRE(std::abs(glm_vector[i] - my_vec[i]) < EPS);
    }
}

TEST_CASE("Construction of vectors, getters") {
    float *numbers2 = new float[2];
    numbers2[0] = 34.7;
    numbers2[1] = -57.12;

    float *numbers3 = new float[3];
    numbers3[0] = 17;
    numbers3[1] = 39.272;
    numbers3[2] = -38;

    float *numbers4 = new float[4];
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

TEST_CASE("Copy of vectors with assignment operator") {
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

TEST_CASE("Vector addition") {
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

TEST_CASE("Vector subtraction") {
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

TEST_CASE("Scalar product of vectors") {
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

TEST_CASE("Cross product of vectors") {
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

TEST_CASE("Multiply vector by float") {
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

TEST_CASE("Divide vector by float") {
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

TEST_CASE("Equality and inequality of vectors") {
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

TEST_CASE("Length of vectors") {
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

TEST_CASE("Vector normalization") {
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

TEST_CASE("Output of vectors") {
    Vector vec1{1}, vec6{-1.123123, 2, 3.002, 4.363, 5, -6};

    std::ostringstream oss1;
    oss1 << vec1;
    REQUIRE(oss1.str() == "Vector[size=1]: [1]");

    std::ostringstream oss2;
    oss2 << vec6;
    REQUIRE(oss2.str() == "Vector[size=6]: [-1.12312, 2, 3.002, 4.363, 5, -6]");
}
