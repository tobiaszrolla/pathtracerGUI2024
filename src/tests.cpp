#include <gtest/gtest.h>
#include "../include/PathTracer.hpp"

//===========================================Vector3D Test===========================================================================//
// Test dla dodawania wektorów
TEST(Vector3DTest, AddTest) {
    Vector3D v1(1, 2, 3);
    Vector3D v2(4, 5, 6);
    Vector3D result = v1.add(v2);
    EXPECT_EQ(result.getX(), 5);
    EXPECT_EQ(result.getY(), 7);
    EXPECT_EQ(result.getZ(), 9);
}

// Test dla iloczynu wektorowego
TEST(Vector3DTest, CrossTest) {
    Vector3D v1(1, 0, 0);
    Vector3D v2(0, 1, 0);
    Vector3D result = v1.cross(v2);
    EXPECT_EQ(result.getX(), 0);
    EXPECT_EQ(result.getY(), 0);
    EXPECT_EQ(result.getZ(), 1);
}

// Test dla normalizacji wektora
TEST(Vector3DTest, NormalizeTest) {
    Vector3D v(3, 0, 0);
    Vector3D result = v.normalise();
    EXPECT_NEAR(result.getX(), 1.0, 1e-6);
    EXPECT_NEAR(result.getY(), 0.0, 1e-6);
    EXPECT_NEAR(result.getZ(), 0.0, 1e-6);
}
// Test dla normalizacji wektora
TEST(Vector3DTest, SubstractionTest) {
    Vector3D v1(1, 2, 3);
    Vector3D v2(4, 5, 6);
    Vector3D result = v1.sub(v2);
    EXPECT_EQ(result.getX(), -3);
    EXPECT_EQ(result.getY(), -3);
    EXPECT_EQ(result.getZ(), -3);
}
TEST(Vector3DTest, SubstractionTest2) {
    Vector3D v1(1, 2, 3);
    Vector3D v2(4, 5, 6);
    Vector3D result = v2.sub(v1);
    EXPECT_EQ(result.getX(), 3);
    EXPECT_EQ(result.getY(), 3);
    EXPECT_EQ(result.getZ(), 3);
}
//===========================================================Triangle==test=======================================================//

// Test przecięcia promienia z trójkątem
/*TEST(MollerTrumboreTest, Intersection) {
    // Wierzchołki trójkąta
    Vector3D v0(0, 0, 0);
    Vector3D v1(1, 0, 0);
    Vector3D v2(0, 1, 0);

    // Tworzymy trójkąt
    Triangle triangle(v0, v1, v2, 1); // MaterialIndex ustawiony na 1

    // Promień przecina trójkąt
    Vector3D rayOrigin(0.2, 0.2, -1);    // Start promienia przed trójkątem
    Vector3D rayDirection(0, 0, 1);      // Kierunek w stronę trójkąta
    Ray ray(rayOrigin, rayDirection);

    // Sprawdź, czy funkcja wykrywa przecięcie
    std::optional<Vector3D> vec = triangle.mollerTrumbore(ray);
    EXPECT_EQ(vec = Vector3D); // Powinien zwrócić materialIndex=1
}
TEST(MollerTrumboreTest, ObliqueDirectionIntersection) {
    // Wierzchołki trójkąta w przestrzeni 3D
    Vector3D v0(1, 0, 0);
    Vector3D v1(3, 0, 0);
    Vector3D v2(2, 2, 0);

    // Tworzymy trójkąt
    Triangle triangle(v0, v1, v2, 4); // MaterialIndex ustawiony na 4

    // Promień startuje i przecina trójkąt pod kątem
    Vector3D rayOrigin(2, -1, -1);    // Punkt startu
    Vector3D rayDirection(0, 1, 1);  // Kierunek pod kątem do X, Y, Z
    Ray ray(rayOrigin, rayDirection.normal()); // Normalizuj kierunek

    // Sprawdź, czy funkcja wykrywa przecięcie
    int materialIndex = triangle.mollerTrumbore(ray);
    EXPECT_EQ(materialIndex, 4); // Powinien zwrócić materialIndex=4
}

// Test braku przecięcia promienia z trójkątem
TEST(MollerTrumboreTest, NoIntersection) {
    // Wierzchołki trójkąta
    Vector3D v0(0, 0, 0);
    Vector3D v1(1, 0, 0);
    Vector3D v2(0, 1, 0);

    // Tworzymy trójkąt
    Triangle triangle(v0, v1, v2, 1); // MaterialIndex ustawiony na 1

    // Promień omija trójkąt
    Vector3D rayOrigin(2, 2, -1);    // Start promienia daleko od trójkąta
    Vector3D rayDirection(0, 0, 1);  // Kierunek w stronę osi Z
    Ray ray(rayOrigin, rayDirection);

    // Sprawdź, czy funkcja wykrywa brak przecięcia
    int materialIndex = triangle.mollerTrumbore(ray);
    EXPECT_EQ(materialIndex, -1); // Powinien zwrócić -1
}

// Test promienia równoległego do płaszczyzny trójkąta
TEST(MollerTrumboreTest, ParallelRay) {
    // Wierzchołki trójkąta
    Vector3D v0(0, 0, 0);
    Vector3D v1(1, 0, 0);
    Vector3D v2(0, 1, 0);

    // Tworzymy trójkąt
    Triangle triangle(v0, v1, v2, 1); // MaterialIndex ustawiony na 1

    // Promień równoległy do płaszczyzny trójkąta
    Vector3D rayOrigin(0.2, 0.2, 1);    // Start promienia nad trójkątem
    Vector3D rayDirection(0, 1, 0);     // Kierunek równoległy do płaszczyzny
    Ray ray(rayOrigin, rayDirection);

    // Sprawdź, czy funkcja wykrywa brak przecięcia
    int materialIndex = triangle.mollerTrumbore(ray);
    EXPECT_EQ(materialIndex, -1); // Powinien zwrócić -1
}*/

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}