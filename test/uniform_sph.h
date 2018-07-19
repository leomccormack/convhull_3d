#ifndef UNIFORM_SPH_H
#define UNIFORM_SPH_H

#ifdef __cplusplus
extern "C" {
#endif
    
/* References:
 [1] McLaren's Improved Snub Cube and Other New Spherical Designs in Three Dimensions", R. H. Hardin and
 N. J. A. Sloane, Discrete and Computational Geometry, 15 (1996), pp. 429-441.
 [2] Gräf, M., & Potts, D. (2011). On the computation of spherical designs by a new optimization
 approach based on fast spherical Fourier transforms. Numerische Mathematik, 119(4), 699-724. */

extern const float __Tdesign_degree_7_dirs_deg[24][2];
extern const float __Tdesign_degree_9_dirs_deg[48][2];
extern const float __Tdesign_degree_18_dirs_deg[180][2];
extern const float __Tdesign_degree_40_dirs_deg[840][2];
extern const float __Tdesign_degree_100_dirs_deg[5100][2];
    
#ifdef __cplusplus
} /*extern "C"*/
#endif


#endif /* UNIFORM_SPH_H */
