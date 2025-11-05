#ifndef _WRAPPER_H
#define _WRAPPER_H

#ifdef __cplusplus
extern "C" { 
#endif

export void w_tone(unsigned char pin, unsigned int frequency);
export void w_noTone(unsigned char pin);

#ifdef __cplusplus
}
#endif

#endif
