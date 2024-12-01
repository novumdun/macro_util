#ifndef __MACRO_BITS_OPT_H__
#define __MACRO_BITS_OPT_H__


#define BITS_MASK(bitsstart, bitsend)       BITS_MASK_LEN((bitsstart), ((bitsend) + 1) - bitsstart)
#define BITS_MASK_LEN(bitsstart, bitslen)   (((1UL << (bitslen)) - 1) << (bitsstart))

#define BITS_MASK_NOT(bitsstart, bitsend)       (~BITS_MASK((bitsstart), (bitsend)))
#define BITS_MASK_NOT_LEN(bitsstart, bitslen)   (~BITS_MASK_LEN((bitsstart), (bitslen)))

#define BITS_UNSET(var, bitsstart, bitsend)         ((var) & BITS_MASK_NOT((bitsstart), (bitsend)))
#define BITS_UNSET_LEN(var, bitsstart, bitslen)     ((var) & BITS_MASK_NOT_LEN((bitsstart), (bitslen)))

#define BITS_SET(var, bitsstart, bitsend)           ((var) | BITS_MASK((bitsstart), (bitsend)))
#define BITS_SET_LEN(var, bitsstart, bitslen)       ((var) | BITS_MASK_LEN((bitsstart), (bitslen)))

#define BITS_SET_VAL(var, bitsstart, bitsend, val)      (BITS_UNSET((var), (bitsstart), (bitsend)) | ((unsigned long long)(val) << (bitsstart)))
#define BITS_SET_VAL_LEN(var, bitsstart, bitslen, val)  (BITS_UNSET_LEN((var), (bitsstart), (bitslen)) | ((unsigned long long)(val) << (bitsstart)))

#define BITS_GET_VAL(var, bitsstart, bitsend)       (((var) >> (bitsstart)) & BITS_MASK(0, (bitsend+1-bitsstart)))
#define BITS_GET_VAL_LEN(var, bitsstart, bitslen)   (((var) >> (bitsstart)) & BITS_MASK_LEN(0, (bitslen)))

#endif
