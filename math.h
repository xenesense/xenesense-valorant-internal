#pragma once

//#include <intrin.h>


#define M_PI	3.1415926535

double radian_to_degree(double degree) {
    return ((degree) * (180.0f / M_PI));
}

double degree_to_radian(double degree) {
    return degree * (M_PI / 180);
}
void angle_vectors(const fvector& angles, fvector* forward)
{
    float    sp, sy, cp, cy;

    sy = crt::custom_sinf(degree_to_radian(angles.y));
    cy = crt::custom_cosf(degree_to_radian(angles.y));

    sp = crt::custom_sinf(degree_to_radian(angles.x));
    cp = crt::custom_cosf(degree_to_radian(angles.x));

    forward->x = cp * cy;
    forward->y = cp * sy;
    forward->z = -sp;
}

typedef union __declspec(intrin_type) __declspec(align(16)) __m128 {
    float               m128_f32[4];
    unsigned __int64    m128_u64[2];
    __int8              m128_i8[16];
    __int16             m128_i16[8];
    __int32             m128_i32[4];
    __int64             m128_i64[2];
    unsigned __int8     m128_u8[16];
    unsigned __int16    m128_u16[8];
    unsigned __int32    m128_u32[4];
} __m128;

extern "C" __m128 _mm_load_ss(const float* _A);
extern "C" __m128 _mm_mul_ss(__m128 _A, __m128 _B);
extern "C" __m128 _mm_rsqrt_ss(__m128 _A);

__forceinline fvector calc_angle(fvector Src, fvector& Dst) {
    fvector Delta = Src - Dst;
    const auto sqrtss = [](float in) {
        __m128 reg = _mm_load_ss(&in);
        return _mm_mul_ss(reg, _mm_rsqrt_ss(reg)).m128_f32[0];
    };

    float hyp = sqrtss(Delta.x * Delta.x + Delta.y * Delta.y + Delta.z * Delta.z);

    fvector Rotation{};
    Rotation.x = radian_to_degree(valorant::math::sdk_acos(Delta.z / hyp)); // mb o_acosf
    Rotation.y = radian_to_degree(valorant::math::sdk_atan(Delta.y / Delta.x)); //mb o_atanf
    Rotation.z = 0;
    if (Delta.x >= 0.0f) Rotation.y += 180.0f;
    Rotation.x += 270.f;
    return Rotation;
}

fvector smooth_aim(fvector Camera_rotation, fvector Target, float SmoothFactor)
{
    fvector diff = Target - Camera_rotation;
    diff.normalize();
    return Camera_rotation + diff / SmoothFactor;
}