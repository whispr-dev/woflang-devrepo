Usage Examples
Vector Add SIMD:

cpp
Copy
Edit
__m256 x1 = _mm256_set1_ps(1.0f);
__m256 y1 = _mm256_set1_ps(2.0f);
__m256 z1 = _mm256_set1_ps(3.0f);

__m256 x2 = _mm256_set1_ps(0.5f);
__m256 y2 = _mm256_set1_ps(1.5f);
__m256 z2 = _mm256_set1_ps(2.5f);

__m256 xr, yr, zr;
woflang::vector_add_3d(x1, y1, z1, x2, y2, z2, xr, yr, zr);
