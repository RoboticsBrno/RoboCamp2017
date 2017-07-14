#include "Color.h"

Rgb::Rgb( Hsv y ) {
    // Formula taken from: https://en.wikipedia.org/wiki/HSL_and_HSV#From_HSV
    uint32_t h = 6 * y.h;
    uint32_t c = y.v * y.s;
    uint32_t x = c * ( 255ul - abs( (uint32_t)h % ( 2 << 8 ) - 255ul ) );
    c >>= 8;
    h >>= 8;
    x >>= 16;
    uint32_t m = y.v - c;
    switch ( h ) {
        case 6:
        case 0: r = c + m; g = x + m; b = m;     break;
        case 1: r = x + m; g = c + m; b = m;     break;
        case 2: r = m;     g = c + m; b = x + m; break;
        case 3: r = m;     g = x + m; b = c + m; break;
        case 4: r = x + m; g = m;     b = c + m; break;
        case 5: r = c + m; g = m;     b = x + m; break;
    }
}

Rgb& Rgb::operator=( Hsv hsv ) {
    Rgb r{ hsv };
    swap( r );
    return *this;
}

Hsv::Hsv( Rgb r ) {
    // Formula taken from http://www.easyrgb.com/en/math.php
    uint32_t min = min( r.r, min( r.g, r.b ) );
    uint32_t max = max( r.r, max( r.g, r.b ) );
    uint32_t delta = max - min;

    v = max;
    if ( delta == 0 ) {
        h = s = 0;
        return;
    }

    s = ( delta << 8 ) / max;
    uint32_t deltaR = ( ( ( ( max - r.r ) / 6 ) + ( max / 2 ) ) << 8 ) / max;
    uint32_t deltaG = ( ( ( ( max - r.g ) / 6 ) + ( max / 2 ) ) << 8 ) / max;
    uint32_t deltaB = ( ( ( ( max - r.b ) / 6 ) + ( max / 2 ) ) << 8 ) / max;

    uint32_t hh;
    if ( max == r.r )
        hh = deltaB - deltaG;
    else if ( max == r.g )
        hh = 255 / 3 + deltaR - deltaB;
    else
        hh = 2 * 255 / 3 + deltaG - deltaR;

    if ( hh < 0 )
        hh += 255;
    if ( h > 255 )
        hh -= 255;
    h = hh;
}

Hsv& Hsv::operator=( Rgb rgb ) {
    Hsv h{ rgb };
    swap( h );
    return *this;
}