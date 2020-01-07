/*
 * Copyright 2012 Red Hat Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Ben Skeggs
 */

#ifndef __NOUVEAU_OS_H__
#define __NOUVEAU_OS_H__

/******************************************************************************
 * types
 *****************************************************************************/
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>

__extension__ typedef unsigned long long u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

__extension__ typedef long long s64;
typedef int32_t s32;
typedef int16_t s16;
typedef int8_t s8;

#ifndef _ASM_GENERIC_INT_LL64_H
__extension__ typedef unsigned long long __u64;
typedef uint32_t __u32;
typedef uint16_t __u16;
typedef uint8_t __u8;
__extension__ typedef long long __s64;
typedef int32_t __s32;
typedef int16_t __s16;
typedef int8_t __s8;
#endif

typedef u64 phys_addr_t;
typedef u64 dma_addr_t;
typedef dma_addr_t resource_size_t;

/******************************************************************************
 * various random macros
 *****************************************************************************/
#define noinline __attribute__ ((noinline))
#define __packed __attribute__ ((packed))
#define __aligned(a) __attribute__((aligned(a)))
#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) > (b) ? (b) : (a))
#define max_t(t,a,b) max((t)(a), (t)(b))
#define min_t(t,a,b) min((t)(a), (t)(b))
#define clamp(a,b,c) min(max((a), (b)), (c))
#define roundup(a,b) ((((a) + ((b) - 1)) / (b)) * (b))
#define round_up(a,b) roundup((a), (b))
#define rounddown(a,b) ((a) / (b) * (b))
#define upper_32_bits(a) ((a) >> 32)
#define lower_32_bits(a) ((a) & 0xffffffff)
#define DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))
#define DIV_ROUND_UP_ULL(n,d) DIV_ROUND_UP((n),(d))
#define DIV_ROUND_CLOSEST(x, divisor)(			\
{							\
	typeof(x) __x = x;				\
	typeof(divisor) __d = divisor;			\
	(((typeof(x))-1) > 0 ||				\
	 ((typeof(divisor))-1) > 0 || (__x) > 0) ?	\
		(((__x) + ((__d) / 2)) / (__d)) :	\
		(((__x) - ((__d) / 2)) / (__d));	\
}							\
)
#define do_div(a,b) (a) = (a) / (b)
#define div_u64(a,b) (a) / (b)
#define div64_s64(a,b) (a) / (b)
#define likely(a) (a)
#define unlikely(a) (a)
#define BIT(a) (1UL << (a))
#define BIT_ULL(a) (1ULL << (a))
#define ALIGN(a,b) (((a) + ((b) - 1)) & ~((b) - 1))
#define ALIGN_DOWN(a,b) ((a) & ~((b) - 1))
#define IS_ALIGNED(a,b) (!((a) & ((b) - 1)))

#define ERR_PTR(err) ((void *)(long)(err))
#define PTR_ERR(ptr) ((long)(ptr))
#define IS_ERR(ptr)  ((unsigned long)(ptr) >= (unsigned long)-4095)
#define IS_ERR_OR_NULL(ptr) ({                                                 \
	void *_ptr = (ptr);                                                    \
	(!_ptr || IS_ERR(_ptr));                                               \
})

#define jiffies (ktime_to_ns(ktime_get()))
#define nsecs_to_jiffies(a) (a)
#define usecs_to_jiffies(a) nsecs_to_jiffies((a) * 1000)
#define msecs_to_jiffies(a) usecs_to_jiffies((a) * 1000)
#define HZ 1000000

#define time_before(a,b) ((a) < (b))
#define time_after_eq(a,b) ((a) >= (b))

#define THIS_MODULE 0
#define request_module(a,b,c)

#define PAGE_SHIFT 12
#define PAGE_SIZE (1 << PAGE_SHIFT)
#define PAGE_MASK (PAGE_SHIFT - 1)

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
#define __acquires(a)
#define __releases(a)
#define __printf(a,b)
#define __user

#if defined(CONFIG_ARM)
#define IS_ENABLED_CONFIG_ARM 1
#else
#define IS_ENABLED_CONFIG_ARM 0
#endif

#if defined(CONFIG_ARM_DMA_USE_IOMMU)
#define IS_ENABLED_CONFIG_ARM_DMA_USE_IOMMU 1
#else
#define IS_ENABLED_CONFIG_ARM_DMA_USE_IOMMU 0
#endif

#if defined(CONFIG_IOMMU_API)
#define IS_ENABLED_CONFIG_IOMMU_API 1
#else
#define IS_ENABLED_CONFIG_IOMMU_API 0
#endif

#if defined(CONFIG_ARCH_TEGRA)
#define IS_ENABLED_CONFIG_ARCH_TEGRA 1
#else
#define IS_ENABLED_CONFIG_ARCH_TEGRA 0
#endif

#if defined(CONFIG_ARCH_TEGRA_186_SOC)
#define IS_ENABLED_CONFIG_ARCH_TEGRA_186_SOC 1
#else
#define IS_ENABLED_CONFIG_ARCH_TEGRA_186_SOC 0
#endif

#if defined(CONFIG_ARCH_TEGRA_210_SOC)
#define IS_ENABLED_CONFIG_ARCH_TEGRA_210_SOC 1
#else
#define IS_ENABLED_CONFIG_ARCH_TEGRA_210_SOC 0
#endif

#define IS_ENABLED(x) IS_ENABLED_##x

static inline bool
is_power_of_2(unsigned long n)
{
	return (n != 0 && ((n & (n - 1)) == 0));
}

static inline int
order_base_2(u64 base)
{
	u64 temp = base >> 1;
	int log2;

	for (log2 = 0; temp; log2++, temp >>= 1) {
	}

	return (base & (base - 1)) ? log2 + 1: log2;
}

#define struct_size(a,b,c) (sizeof(*(a)) + sizeof(*(a)->b) * (c))
#define array3_size(a,b,c) ((c) * (a) * (b))

/******************************************************************************
 * errno
 *****************************************************************************/

#define ENOTSUPP 524


/******************************************************************************
 * endianness
 *****************************************************************************/

#include <endian.h>

#define le16_to_cpu(a) le16toh(a)
#define le32_to_cpu(a) le32toh(a)
#define cpu_to_le16(a) htole16(a)
#define cpu_to_le32(a) htole32(a)

/******************************************************************************
 * unaligned access
 *****************************************************************************/

static inline u16
get_unaligned_le16(void *ptr)
{
	return le16_to_cpu(*(u16 *)ptr);
}

static inline u32
get_unaligned_le32(void *ptr)
{
	return le32_to_cpu(*(u32 *)ptr);
}

static inline void
put_unaligned_le16(u16 val, void *ptr)
{
	*(u16 *)ptr = cpu_to_le16(val);
}

static inline void
put_unaligned_le32(u32 val, void *ptr)
{
	*(u32 *)ptr = cpu_to_le32(val);
}

/******************************************************************************
 * bitops
 *****************************************************************************/
#define __ffs64(a) (__builtin_ffsll(a) - 1)
#define __ffs(a) (__builtin_ffs(a) - 1)
#define fls(a) ((a) ? sizeof(a) * 8 - __builtin_clz(a) : 0)
#define fls64(a) ((a) ? sizeof(a) * 8 - __builtin_clzll(a) : 0)

static inline int
hweight8(u32 v) {
	int i = 0;
	while (v) {
		i += (v & 1);
		v >>= 1;
	}
	return i;
}

static inline int
hweight32(u32 v) {
	int i = 0;
	while (v) {
		i += (v & 1);
		v >>= 1;
	}
	return i;
}

#define BITS_PER_BYTE 8
#define BITS_PER_LONG (sizeof(unsigned long) * 8)
#define BITS_TO_LONGS(b) DIV_ROUND_UP((b), BITS_PER_LONG)
#define DECLARE_BITMAP(n,b) unsigned long n[BITS_TO_LONGS(b)]
#define BITMAP_POS(b) ((b) / BITS_PER_LONG)
#define BITMAP_BIT(b) ((b) % BITS_PER_LONG)

static inline int
test_bit(int bit, const volatile unsigned long *ptr)
{
	return !!(ptr[BITMAP_POS(bit)] & (1UL << BITMAP_BIT(bit)));
}

static inline int
__test_and_clear_bit(int bit, volatile unsigned long *ptr)
{
	int ret = test_bit(bit, ptr);
	*ptr &= ~(1L << bit);
	return ret;
}

static inline int
test_and_clear_bit(int bit, volatile unsigned long *ptr)
{
	return !!(__sync_fetch_and_and(ptr, ~(1L << bit)) & (1L << bit));
}

static inline int
__test_and_set_bit(int bit, volatile unsigned long *ptr)
{
	int ret = test_bit(bit, ptr);
	*ptr |= (1L << bit);
	return ret;
}

static inline int
test_and_set_bit(int bit, volatile unsigned long *ptr)
{
	 return !!(__sync_fetch_and_or(ptr, (1L << bit)) & (1L << bit));
}

static inline void
clear_bit(int bit, volatile unsigned long *ptr)
{
	test_and_clear_bit(bit, ptr);
}

static inline void
set_bit(int bit, volatile unsigned long *ptr)
{
	test_and_set_bit(bit, ptr);
}

static inline void
__clear_bit(long bit, volatile unsigned long *addr)
{
	addr[BITMAP_POS(bit)] &= ~(1UL << BITMAP_BIT(bit));
}

static inline void
__set_bit(long bit, volatile unsigned long *addr)
{
	addr[BITMAP_POS(bit)] |= (1UL << BITMAP_BIT(bit));
}

static inline long
find_next_bit(const volatile unsigned long *addr, int bits, int bit)
{
	while (bit < bits) {
		if (test_bit(bit, addr))
			break;
		bit++;
	}
	return bit;
}

static inline long
find_first_zero_bit(volatile unsigned long *addr, int bits)
{
	int bit;
	for (bit = 0; bit < bits; bit++) {
		if (!test_bit(bit, addr))
			break;
	}
	return bit;
}

static inline void
bitmap_fill(unsigned long *addr, unsigned int bits)
{
	int bit;
	for (bit = 0; bit < bits; bit++)
		__set_bit(bit, addr);
}

static inline void
bitmap_clear(unsigned long *addr, unsigned int pos, unsigned int bits)
{
	while (bits--)
		__clear_bit(pos++, addr);
}

#define for_each_set_bit(bit, addr, size)                                      \
	for ((bit) = find_next_bit((addr), (size), 0); (bit) < (size);         \
	     (bit) = find_next_bit((addr), (size), (bit) + 1))

/******************************************************************************
 * atomics
 *****************************************************************************/
typedef struct atomic {
	int value;
} atomic_t;

#define atomic_read(a) ((a)->value)
#define atomic_set(a,b) ((a)->value = (b))
#define atomic_inc(a) ((void) __sync_fetch_and_add (&(a)->value, 1))
#define atomic_dec(a) ((void) __sync_fetch_and_add (&(a)->value, -1))
#define atomic_add(a,b) ((void) __sync_add_and_fetch(&(a)->value, (b)))
#define atomic_add_return(b,a) (__sync_add_and_fetch(&(a)->value, (b)))
#define atomic_inc_return(a) atomic_add_return(1, (a))
#define atomic_dec_return(a) atomic_add_return(-1, (a))
#define atomic_dec_and_test(a) (atomic_dec_return(a) == 0)
#define atomic_or(a,b) (void) __sync_fetch_and_or(&(b)->value, (a));
#define atomic_xchg(a,b) \
	__atomic_exchange_n(&(a)->value, (b), __ATOMIC_SEQ_CST)

static inline bool
atomic_inc_not_zero(atomic_t *a)
{
	int v = atomic_read(a);
	while (v) {
		int p = __sync_val_compare_and_swap(&a->value, v, v + 1);
		if (p == v)
			break;
		v = p;
	}
	return v != 0;
}

/******************************************************************************
 * refcount
 *****************************************************************************/
typedef struct refcount {
	atomic_t atomic;
} refcount_t;

#define refcount_set(a,b) atomic_set(&(a)->atomic, (b))
#define refcount_inc(a) atomic_inc(&(a)->atomic)
#define refcount_inc_not_zero(a) atomic_inc_not_zero(&(a)->atomic)
#define refcount_dec_and_test(a) atomic_dec_and_test(&(a)->atomic)
#define refcount_dec_and_mutex_lock(a,b) ({                                    \
	struct mutex *_m = (b);                                                \
	bool _locked = true;                                                   \
	mutex_lock(_m);                                                        \
	if (!refcount_dec_and_test(a)) {                                       \
		mutex_unlock(_m);                                              \
		_locked = false;                                               \
	}                                                                      \
	_locked;                                                               \
})

/******************************************************************************
 * krefs
 *****************************************************************************/
struct kref {
	refcount_t refcount;
};

#define kref_init(a) refcount_set(&(a)->refcount, 1)
#define kref_get(a) refcount_inc(&(a)->refcount)
#define kref_put(a,b) if (refcount_dec_and_test(&(a)->refcount)) b(a)

/******************************************************************************
 * ktime
 *****************************************************************************/
#include <time.h>

typedef struct timespec ktime_t;

static inline ktime_t
ktime_get(void)
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ts;
}

static inline s64
ktime_to_ns(ktime_t kt)
{
	return (s64)kt.tv_sec * 1000000000 + kt.tv_nsec;
}

static inline s64
ktime_to_us(ktime_t kt)
{
	return ktime_to_ns(kt) / 1000;
}

/******************************************************************************
 * string
 *****************************************************************************/
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define kstrdup(a,b) strdup((a))
#define kstrndup(a,b,c) strndup((a), (b))

static inline int
kstrtol(const char *s, unsigned int base, long *res)
{
	errno = 0;
	*res = strtol(s, NULL, base);
	if (errno && *res == LONG_MAX)
		return errno;
	if (errno && *res == 0)
		return errno;
	return 0;
}

static inline int
kstrtoul(const char *s, unsigned int base, unsigned long *res)
{
	errno = 0;
	*res = strtoul(s, NULL, base);
	if (errno && *res == ULONG_MAX)
		return errno;
	if (errno && *res == 0)
		return errno;
	return 0;
}

/******************************************************************************
 * printk
 *****************************************************************************/
#include <stdarg.h>
#include <stdio.h>

#define KERN_CRIT ""
#define KERN_ERR ""
#define KERN_WARNING ""
#define KERN_INFO ""
#define KERN_DEBUG ""
#define KERN_CONT ""

#define printk printf
#define vprintk vprintf

#define pr_err(f,a...) printk(KERN_ERR f, ##a)

/******************************************************************************
 * memory
 *****************************************************************************/
#define GFP_KERNEL    1
#define __GFP_ZERO    2
#define GFP_DMA32     4
#define GFP_USER      8
#define GFP_HIGHUSER 16

typedef unsigned gfp_t;

#define vmalloc malloc
#define vfree free
#define kmalloc(a,b) malloc((a))
#define kmalloc_array(a,b,c) kmalloc((b) * (a), (c))
#define kzalloc(a,b) calloc(1, (a))
#define kcalloc(a,b,c) calloc((a), (b))
#define kfree free
#define kvmalloc(a,b) kmalloc((a), (b))
#define kvmalloc_array(a,b,c) kvmalloc((b) * (a), (c))
#define kvzalloc(a,b) kzalloc((a), (b))
#define kvcalloc(a,b,c) kcalloc((a), (b), (c))
#define kvfree(a) kfree(a)

#define vzalloc(a) calloc(1, (a))
#define vfree free

static inline void *
kmemdup(const void *src, size_t len, gfp_t gfp)
{
	void *dst = malloc(len);
	if (dst)
		memcpy(dst, src, len);
	return dst;
}

struct page {
};

static inline struct page *
alloc_page(gfp_t gfp)
{
	return NULL;
}

static inline void
__free_page(struct page *page)
{
}

static inline dma_addr_t
page_to_phys(struct page *page)
{
	return 0;
}

static inline struct page *
pfn_to_page(dma_addr_t pfn)
{
	return NULL;
}

static inline dma_addr_t
page_to_pfn(struct page *page)
{
	return 0;
}

static inline unsigned long
get_num_physpages(void)
{
	return 0;
}

typedef struct {
	unsigned long pgprot;
} pgprot_t;

#define __pgprot(x) ((pgprot_t) { (x) } )
#define pgprot_noncached(prot) (prot)
#define pgprot_writecombine pgprot_noncached

#define PAGE_KERNEL __pgprot(0)

#define VM_MAP 4

static inline void *
vmap(struct page **pages, unsigned int count,
     unsigned long flags, pgprot_t prot)
{
	return NULL;
}

static inline void
vunmap(const void *addr)
{
}

/******************************************************************************
 * assertions
 *****************************************************************************/
#include <assert.h>
#include <execinfo.h>

static inline void
nvos_backtrace(void)
{
	void **buffer;
	char **sinfo;
	int ninfo, i;

	buffer = malloc(sizeof(*buffer) * 512);
	ninfo = backtrace(buffer, 512);
	sinfo = backtrace_symbols(buffer, ninfo);
	if (sinfo) {
		for (i = 0; i < ninfo; i++)
			printf("%s\n", sinfo[i]);
		free(sinfo);
	}
	free(buffer);
}

#define BUG() do {                                                             \
	printk("BUG at %s:%d/%s()!\n\n", __FILE__, __LINE__, __func__);        \
	nvos_backtrace();                                                      \
	assert(0);                                                             \
} while(0)

#define BUG_ON(c) do { if ((c)) BUG(); } while(0)

#define __WARN() do {                                                          \
	printk("WARNING at %s:%d/%s()!\n\n", __FILE__, __LINE__, __func__);    \
	nvos_backtrace();                                                      \
} while(0)

#define WARN(c,f...) ({                                                        \
	int _ret = !!(c);                                                      \
	if (_ret) {                                                            \
		printk(f);                                                     \
		__WARN();                                                      \
	};                                                                     \
	_ret;                                                                  \
})

#define WARN_ON(c) ({                                                          \
	int _ret = !!(c);                                                      \
	if (_ret)                                                              \
		__WARN();                                                      \
	_ret;                                                                  \
})

#define WARN_ON_ONCE(c) ({                                                     \
	static int _once = 1;                                                  \
	int _ret = !!(c);                                                      \
	if (_ret && _once) {                                                   \
		__WARN();                                                      \
		_once = 0;                                                     \
	}                                                                      \
	_ret;                                                                  \
})

/******************************************************************************
 * interrupts
 *****************************************************************************/
#define IRQF_SHARED 0

typedef enum irqreturn {
	IRQ_NONE,
	IRQ_HANDLED
} irqreturn_t;

typedef irqreturn_t (*irq_handler_t)(int, void *);

extern int  os_intr_init(unsigned int, irq_handler_t, unsigned long,
			 const char *, void *);
extern void os_intr_free(unsigned int, void *);

#define request_irq os_intr_init
#define free_irq os_intr_free

/******************************************************************************
 * spinlocks - using pthread mutex due to no static spinlock initialiser
 *****************************************************************************/
#include <pthread.h>

typedef struct spinlock_t {
	pthread_mutex_t lock;
} spinlock_t;

#define DEFINE_SPINLOCK(a) spinlock_t a = { .lock = PTHREAD_MUTEX_INITIALIZER }

#define spin_lock_init(a) do {                                                 \
	(a)->lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;                \
} while(0)
#define spin_lock(a) pthread_mutex_lock(&(a)->lock)
#define spin_unlock(a) pthread_mutex_unlock(&(a)->lock)
#define spin_lock_irqsave(a,b) do { (b) = 1; spin_lock((a)); } while (0)
#define spin_unlock_irqrestore(a,b) do { (void)(b); spin_unlock((a)); } while (0)
#define spin_is_locked(a) ({ \
	int _ret = pthread_mutex_trylock(&(a)->lock) != 0; \
	if (_ret == 0) \
		pthread_mutex_unlock(&(a)->lock); \
	_ret; \
})
#define assert_spin_locked(a) BUG_ON(!spin_is_locked(a))

/******************************************************************************
 * rwlocks
 *****************************************************************************/
typedef struct rwlock_t {
	pthread_rwlock_t lock;
} rwlock_t;

#define rwlock_init(a) pthread_rwlock_init(&(a)->lock, NULL)
#define read_lock(a) pthread_rwlock_rdlock(&(a)->lock)
#define read_unlock(a) pthread_rwlock_unlock(&(a)->lock)
#define write_lock_irq(a) pthread_rwlock_wrlock(&(a)->lock)
#define write_unlock_irq(a) pthread_rwlock_unlock(&(a)->lock)

/******************************************************************************
 * mutexes
 *****************************************************************************/
struct mutex {
	pthread_mutex_t mutex;
};

#define DEFINE_MUTEX(a) struct mutex a = { .mutex = PTHREAD_MUTEX_INITIALIZER }
#define mutex_init(a) pthread_mutex_init(&(a)->mutex, NULL)
#define mutex_lock(a) pthread_mutex_lock(&(a)->mutex)
#define mutex_unlock(a) pthread_mutex_unlock(&(a)->mutex)

/******************************************************************************
 * lockdep
 *****************************************************************************/
struct lock_class_key {
};

#define __mutex_init(a,b,c) do {                                               \
	struct lock_class_key *__key = (c); (void)__key;                       \
	pthread_mutex_init(&(a)->mutex, NULL);                                 \
} while(0)

/******************************************************************************
 * lists
 *****************************************************************************/
#include "list.h"

#define list_first_entry_or_null(a,b,c) \
	(list_empty(a) ? NULL : list_first_entry((a),b,c))
#define list_for_each_entry_from_reverse(a,b,c) \
	for (; &a->c != (b); a = list_entry((a)->c.prev, typeof(*(a)), c))

/******************************************************************************
 * rbtree
 *****************************************************************************/
struct rb_root {
	struct rb_node *rb_node;
};

#define RB_ROOT (struct rb_root) {}

struct rb_node {
	struct rb_node *parent;
	struct rb_node *rb_left;
	struct rb_node *rb_right;
};

#define rb_entry(a,b,c) container_of(a,b,c)

#define RB_EMPTY_NODE(a) ((a)->parent == (a))
#define RB_CLEAR_NODE(a) ((a)->parent = (a))

void rb_link_node(struct rb_node *, struct rb_node *, struct rb_node **);
void rb_insert_color(struct rb_node *, struct rb_root *);
void rb_erase(struct rb_node *, struct rb_root *);
struct rb_node *rb_first(struct rb_root *);
struct rb_node *rb_next(struct rb_node *);

/******************************************************************************
 * io space
 *****************************************************************************/
#define __iomem

void __iomem *nvos_ioremap(u64 addr, u64 size);
void  nvos_iounmap(void __iomem *ptr);

#define ioremap(a,b) nvos_ioremap((a), (b))
#define ioremap_wc ioremap
#define iounmap(a) nvos_iounmap((a))

#define ioread8(a) *((volatile u8 *)(a))
#define ioread16(a) *((volatile u16 *)(a))
#define ioread32(a) *((volatile u32 *)(a))

#define iowrite8(b,a) *((volatile u8 *)(a)) = (b)
#define iowrite16(b,a) *((volatile u16 *)(a)) = (b)
#define iowrite32(b,a) *((volatile u32 *)(a)) = (b)

#define memset_io memset
#define memcpy_fromio memcpy
#define memcpy_toio memcpy
#define wmb()

static inline int
arch_phys_wc_add(u64 base, u64 size)
{
	return -1;
}

static inline void
arch_phys_wc_del(int index)
{
}

/******************************************************************************
 * io mapping
 *****************************************************************************/
struct io_mapping {
};

static inline struct io_mapping *
io_mapping_create_wc(u64 addr, u64 size)
{
	return NULL;
}

static inline void
io_mapping_free(struct io_mapping *io)
{
}

static inline void __iomem *
io_mapping_map_atomic_wc(struct io_mapping *io, u32 offset)
{
	return NULL;
}

static inline void
io_mapping_unmap_atomic(void __iomem *p)
{
}

/******************************************************************************
 * DMI
 *****************************************************************************/
struct dmi_strmatch {
};

struct dmi_system_id {
	const char *ident;
	struct dmi_strmatch matches[4];
};

#define DMI_MATCH(a, b) { }

static inline int
dmi_check_system(const struct dmi_system_id *list)
{
	return 0;
}

/******************************************************************************
 * Device
 *****************************************************************************/
struct device_driver {
};

struct device {
	struct device_driver *driver;
	char name[64];
	void *pm_domain;
};

#define dev_name(d) (d)->name
#define dev_crit(d,f,a...)   printf("nouveau %s: "f, dev_name(d), ##a)
#define dev_err(d,f,a...)    dev_crit((d), f, ##a)
#define dev_dbg(d,f,a...)    dev_crit((d), f, ##a)
#define dev_warn(d,f,a...)   dev_crit((d), f, ##a)
#define dev_notice(d,f,a...) dev_crit((d), f, ##a)
#define dev_info(d,f,a...)   dev_crit((d), f, ##a)

#define dev_WARN(d,f,a...) WARN("nouveau %s: "f, dev_name(d), ##a);

/******************************************************************************
 * PM runtime
 *****************************************************************************/
static inline void
pm_runtime_mark_last_busy(struct device *dev)
{
}

/******************************************************************************
 * ioport
 *****************************************************************************/
struct resource {
	resource_size_t start;
	resource_size_t end;
};

#define IORESOURCE_MEM 1

static inline resource_size_t
resource_size(const struct resource *res)
{
	return res->end - res->start + 1;
}

/******************************************************************************
 * OpenFirmware
 *****************************************************************************/

struct device_node {
};

static inline const void *
of_get_property(const struct device_node *dn, const char *name, int *lenp)
{
	return NULL;
}

/******************************************************************************
 * dma-mapping
 *****************************************************************************/

static inline void *
dma_alloc_coherent(struct device *dev, size_t sz, dma_addr_t *hdl, gfp_t gfp)
{
	return NULL;
}

static inline void
dma_free_coherent(struct device *dev, size_t sz, void *vaddr, dma_addr_t bus)
{
}

enum dma_attr {
	DMA_ATTR_WRITE_BARRIER,
	DMA_ATTR_WEAK_ORDERING,
	DMA_ATTR_WRITE_COMBINE,
	DMA_ATTR_NON_CONSISTENT,
	DMA_ATTR_NO_KERNEL_MAPPING,
	DMA_ATTR_SKIP_CPU_SYNC,
	DMA_ATTR_FORCE_CONTIGUOUS,
	DMA_ATTR_MAX,
};

static inline void *
dma_alloc_attrs(struct device *dev, size_t sz, dma_addr_t *hdl, gfp_t gfp,
		unsigned long attrs)
{
	return NULL;
}

static inline void
dma_free_attrs(struct device *dev, size_t sz, void *vaddr, dma_addr_t bus,
	       unsigned long attrs)
{
}

/******************************************************************************
 * Bus
 *****************************************************************************/

struct bus_type {
};

extern struct bus_type platform_bus_type;

/******************************************************************************
 * IOMMU
 *****************************************************************************/
struct iommu_domain;

struct iommu_ops {
	unsigned long pgsize_bitmap;
};

struct iommu_domain {
	const struct iommu_ops *ops;
};

#define IOMMU_READ     (1 << 0)
#define IOMMU_WRITE    (1 << 1)
#define IOMMU_CACHE    (1 << 2) /* DMA cache coherency */
#define IOMMU_NOEXEC   (1 << 3)

static inline bool
iommu_present(struct bus_type *bus)
{
	return false;
}

static inline struct iommu_domain *
iommu_domain_alloc(struct bus_type *bus)
{
	return NULL;
}

static inline void
iommu_domain_free(struct iommu_domain *domain)
{
}

static inline int
iommu_attach_device(struct iommu_domain *domain, struct device *dev)
{
	return -ENOSYS;
}

static inline void
iommu_detach_device(struct iommu_domain *domain, struct device *dev)
{
}

static inline int
iommu_map(struct iommu_domain *domain, unsigned long iova, dma_addr_t paddr,
	  size_t size, int prot)
{
	return 0;
}

static inline size_t
iommu_unmap(struct iommu_domain *domain, unsigned long iova, size_t size)
{
	return 0;
}

struct iommu_fwspec {
	u32 ids[1];
};

static inline struct iommu_fwspec *
dev_iommu_fwspec_get(struct device *dev)
{
	return NULL;
}

/******************************************************************************
 * DMA
 *****************************************************************************/
#define DMA_BIT_MASK(a) (((a) == 64) ? ~0ULL : ((1ULL << (a)) - 1))

static inline dma_addr_t
dma_map_page(struct device *pdev, struct page *page, int offset,
	     int length, unsigned flags)
{
	return 0;
}


static inline bool
dma_mapping_error(struct device *pdev, dma_addr_t addr)
{
	return true;
}

static inline void
dma_unmap_page(struct device *pdev, dma_addr_t addr, int size, unsigned flags)
{
}

static inline int
dma_set_mask(struct device *dev, u64 mask)
{
	return 0;
}

static inline int
dma_set_mask_and_coherent(struct device *dev, u64 mask)
{
	return 0;
}

/******************************************************************************
 * PCI
 *****************************************************************************/
#include <pciaccess.h>

#define DMA_BIDIRECTIONAL 1

#define PCI_CAP_ID_AGP 0x02

enum pci_bus_speed {
	PCIE_SPEED_2_5GT,
	PCIE_SPEED_5_0GT,
	PCIE_SPEED_8_0GT,
};

struct pci_bus {
	u16 domain;
	u8  number;
	enum pci_bus_speed max_bus_speed;
};

struct pci_dev {
	struct pci_device *pdev;
	struct device dev;
	u16 vendor;
	u16 device;
	u16 subsystem_vendor;
	u16 subsystem_device;
	int irq;
	struct pci_bus _bus;
	struct pci_bus *bus;
	u8 devfn;
};

static inline void
pci_disable_device(struct pci_dev *pdev)
{
}

static inline int
pci_enable_device(struct pci_dev *pdev)
{
	return 0;
}

static inline void
pci_set_master(struct pci_dev *pdev)
{
}

static inline struct device_node *
pci_device_to_OF_node(const struct pci_dev *pdev)
{
	return NULL;
}

static inline int
pci_find_capability(struct pci_dev *pdev, int cap)
{
	return 0;
}

static inline bool
pci_is_pcie(struct pci_dev *pdev)
{
	return false;
}

static inline int
pci_write_config_byte(struct pci_dev *pdev, int addr, u8 data)
{
	return pci_device_cfg_write_u8(pdev->pdev, data, addr);
}

static inline u64
pci_resource_start(struct pci_dev *pdev, int bar)
{
	return pdev->pdev->regions[bar].base_addr;
}

static inline u64
pci_resource_len(struct pci_dev *pdev, int bar)
{
	return pdev->pdev->regions[bar].size;
}

static inline int
pci_enable_rom(struct pci_dev *pdev)
{
	return 0;
}

static inline void
pci_disable_rom(struct pci_dev *pdev)
{
}

static inline void __iomem *
pci_map_rom(struct pci_dev *pdev, size_t *size)
{
	void *buf;
	*size = pdev->pdev->rom_size;
	buf = malloc(*size);
	if (buf) {
		if (pci_device_read_rom(pdev->pdev, buf)) {
			free(buf);
			buf = NULL;
		}
	}
	return buf;
}

static inline void
pci_unmap_rom(struct pci_dev *pdev, void __iomem *rom)
{
	free(rom);
}

static inline void __iomem *
pci_platform_rom(struct pci_dev *pdev, size_t *size)
{
	return NULL;
}

static inline void *
pci_alloc_consistent(struct pci_dev *hwdev, size_t size,
		     dma_addr_t *dma_handle)
{
	return NULL;
}

static inline void
pci_free_consistent(struct pci_dev *hwdev, size_t size,
		    void *vaddr, dma_addr_t dma_handle)
{
}

static inline int
pci_enable_msi(struct pci_dev *pdev)
{
	return -ENOSYS;
}

static inline void
pci_disable_msi(struct pci_dev *pdev)
{
}

#define PCI_DEVFN(a,b) (((a) << 3) | (b))
#define PCI_SLOT(a) ((a) >> 3)
#define PCI_FUNC(a) ((a) & 0x07)
#define pci_domain_nr(a) (a)->domain
#define pci_get_bus_and_slot(a, b) NULL
#define pci_get_domain_bus_and_slot(a,b,c) ({ (void)(a); NULL; })
#define pci_read_config_dword(a,b,c) *(c) = 0
#define dev_is_pci(a) ({ (void)(a); true; })
#define to_pci_dev(a) container_of((a), struct pci_dev, dev)

#define PCI_ANY_ID (~0)

#define PCI_VENDOR_ID_SI 0x1039
#define PCI_VENDOR_ID_NVIDIA 0x10de
#define PCI_VENDOR_ID_VIA 0x1106

/******************************************************************************
 * AGP
 *****************************************************************************/
#define PCI_AGP_COMMAND_FW 0x10

#ifdef CONFIG_AGP
struct agp_bridge_data {
};

struct agp_kern_info {
	struct pci_dev *device;
	unsigned long mode;
	unsigned long aper_base;
	size_t aper_size;
	bool cant_use_aperture;
};

static inline struct agp_bridge_data *
agp_backend_acquire(struct pci_dev *pdev)
{
	return NULL;
}

static inline void
agp_backend_release(struct agp_bridge_data *bridge)
{
}

static inline int
agp_copy_info(struct agp_bridge_data *bridge, struct agp_kern_info *info)
{
	return -ENOSYS;
}

static inline void
agp_enable(struct agp_bridge_data *bridge, u32 mode)
{
}
#endif

/******************************************************************************
 * platform device
 *****************************************************************************/

struct platform_device {
	struct device dev;
	u64 id;
};

static inline struct resource *
platform_get_resource(struct platform_device *pdev, unsigned int type,
		      unsigned int num)
{
	return NULL;
}

static inline int
platform_get_irq_byname(struct platform_device *pdev, const char *name)
{
	return -1;
}

/******************************************************************************
 * sg table
 *****************************************************************************/
struct scatterlist {
};

struct sg_table {
	struct scatterlist *sgl;
	unsigned int nents;
};

#define for_each_sg(sglist, sg, nr, __i)	                               \
	for (__i = 0, sg = (sglist); __i < (nr); __i++, sg = sg_next(sg))
#define sg_next(a) (a)
#define sg_dma_address(a) 0ULL
#define sg_dma_len(a) 0ULL

/******************************************************************************
 * firmware
 *****************************************************************************/
#include <unistd.h>
#include <fcntl.h>

struct firmware {
	size_t size;
	const u8 *data;
};

int request_firmware(const struct firmware **, const char *, struct device *);
void release_firmware(const struct firmware *);
#define firmware_request_nowarn request_firmware

#define MODULE_FIRMWARE(a)

/******************************************************************************
 * workqueues
 *****************************************************************************/
struct workqueue_struct {
};

static inline struct workqueue_struct *
create_singlethread_workqueue(const char *name)
{
	return (void *)1;
}

static inline void
destroy_workqueue(struct workqueue_struct *wq)
{
	assert(wq);
}

struct work_struct {
	union {
		void (*func)(struct work_struct *);
		void (*exec)(void *);
	};
	struct nvos_work *nvos;
};

#define INIT_WORK(a,b) ((a)->func = (b), (a)->nvos = NULL)
#define schedule_work(a) BUG_ON(!nvos_work_init((a)->exec, (a), &(a)->nvos))
#define flush_work(a) nvos_work_fini(&(a)->nvos)

bool nvos_work_init(void (*)(void *), void *, struct nvos_work **);
void nvos_work_fini(struct nvos_work **);

static inline void
queue_work(struct workqueue_struct *wq, struct work_struct *work)
{
	schedule_work(work);
}

/******************************************************************************
 * waitqueues
 *****************************************************************************/
typedef struct __wait_queue_head {
} wait_queue_head_t;

#define init_waitqueue_head(wq) (void)(wq)
#define wake_up(wq) (void)(wq)
#define wake_up_all(wq) (void)(wq)

#define wait_event(wq,cond) do {                                               \
	(void)(wq);                                                            \
	usleep(1);                                                             \
} while (!(cond))

#define wait_event_interruptible(wq,cond) ({                                   \
	wait_event((wq), (cond)); 0;                                           \
})

#define wait_event_timeout(wq,cond,jiffies) ({                                 \
	unsigned long _t = (jiffies) / 10000;                                  \
	(void)(wq);                                                            \
	do {                                                                   \
		if (cond)                                                      \
			break;                                                 \
		usleep(10);                                                    \
	} while (--_t > 0);                                                    \
	_t;                                                                    \
})

#define wait_event_interruptible_timeout(wq,cond,jiffies)                      \
	wait_event_timeout((wq), (cond), (jiffies))

/******************************************************************************
 * completion
 *****************************************************************************/
struct completion {
	unsigned int done;
};

#define DECLARE_COMPLETION_ONSTACK(c)                                          \
	struct completion c = {}

static inline void
init_completion(struct completion *c)
{
	c->done = 0;
}

static inline void
reinit_completion(struct completion *c)
{
}

static inline unsigned long
wait_for_completion_timeout(struct completion *c, unsigned long timeout)
{
	while (!c->done)
		sched_yield();
	return 1;
}

static inline void
complete(struct completion *c)
{
	c->done = 1;
}

static inline void
complete_all(struct completion *c)
{
	complete(c);
}

/******************************************************************************
 * i2c
 *****************************************************************************/
struct i2c_adapter {
	struct {
		void *parent;
	} dev;
	const struct i2c_algorithm *algo;
	char name[48];
	void *algo_data;
	void *adapdata;
	int owner;
};

#define I2C_M_RD 1

struct i2c_msg {
	u16 addr;
	u16 flags;
	u16 len;
	u8 *buf;
};

#define I2C_FUNC_I2C 1
#define I2C_FUNC_SMBUS_EMUL 2

struct i2c_algorithm {
	int (*master_xfer)(struct i2c_adapter *, struct i2c_msg *, int);
	u32 (*functionality)(struct i2c_adapter *);
};

struct i2c_board_info {
	char type[64];
	unsigned short addr;
};

#define I2C_BOARD_INFO(a,b) .type = (a), .addr = (b)

struct i2c_client {
	struct device dev;
};

struct i2c_driver {
	struct device_driver driver;
	int (*detect)(struct i2c_client *, struct i2c_board_info *);
};

static inline struct i2c_driver *
to_i2c_driver(struct device_driver *driver)
{
	return (void *)driver;
}

static inline struct i2c_client *
i2c_new_device(struct i2c_adapter *adap, struct i2c_board_info const *info)
{
	return NULL;
}

static inline void
i2c_unregister_device(struct i2c_client *client)
{
}

static inline int
i2c_add_adapter(struct i2c_adapter *a)
{
	return 0;
}

static inline int
i2c_del_adapter(struct i2c_adapter *a)
{
	return 0;
}

static inline void *
i2c_get_adapdata(const struct i2c_adapter *a)
{
	return a->adapdata;
}

static inline void
i2c_set_adapdata(struct i2c_adapter *a, void *d)
{
	a->adapdata = d;
}

static inline int
i2c_transfer(struct i2c_adapter *a, struct i2c_msg *m, int num)
{
	if (a->algo)
		return a->algo->master_xfer(a, m, num);
	return -ENODEV;
}

/******************************************************************************
 * i2c bit-bang
 *****************************************************************************/

struct i2c_algo_bit_data {
	int udelay;
	unsigned long timeout;
	void *data;
	void (*setsda) (void *data, int state);
	void (*setscl) (void *data, int state);
	int  (*getsda) (void *data);
	int  (*getscl) (void *data);
	int  (*pre_xfer)(struct i2c_adapter *);
	void (*post_xfer)(struct i2c_adapter *);
};

static inline int
i2c_bit_add_bus(struct i2c_adapter *a)
{
	return 0;
}

extern const struct i2c_algorithm i2c_bit_algo;

/******************************************************************************
 * delay
 *****************************************************************************/
#include <unistd.h>

#define udelay(a) usleep((a))
#define mdelay(a) usleep((a) * 1000)
#define msleep(a) usleep((a) * 1000)
#define usleep_range(a,b) usleep((a))

/******************************************************************************
 * reboot
 *****************************************************************************/
static inline int
orderly_poweroff(bool force)
{
	BUG();
}

/******************************************************************************
 * power supply
 *****************************************************************************/
static inline int
power_supply_is_system_supplied(void)
{
	return -ENOSYS;
}

/******************************************************************************
 * notifier
 *****************************************************************************/
struct notifier_block {
};

/******************************************************************************
 * clk
 *****************************************************************************/
struct clk {
};

static inline struct clk *
clk_get(struct device *dev, const char *id)
{
	return NULL;
}

static inline unsigned long
clk_get_rate(struct clk *clk)
{
	return 0;
}

static inline int
clk_set_rate(struct clk *clk, unsigned long rate)
{
	return -ENOSYS;
}

static inline int
clk_prepare_enable(struct clk *clk)
{
	return -ENOSYS;
}

static inline void
clk_disable_unprepare(struct clk *clk)
{
}

/******************************************************************************
 * regulator
 *****************************************************************************/

struct regulator {
};

static inline int
regulator_set_voltage(struct regulator *regulator, int min_uV, int max_uV)
{
	return -ENOSYS;
}

static inline int
regulator_get_voltage(struct regulator *regulator)
{
	return -ENOSYS;
}

static inline int
regulator_enable(struct regulator *regulator)
{
	return -ENOSYS;
}

static inline int
regulator_disable(struct regulator *regulator)
{
	return -ENOSYS;
}

static inline struct regulator *
regulator_get(struct device *dev, const char *id)
{
	return NULL;
}

/******************************************************************************
 * reset
 *****************************************************************************/

struct reset_control {
};

static inline struct reset_control *
reset_control_get(struct device *dev, const char *id)
{
	return NULL;
}

static inline int
reset_control_assert(struct reset_control *reset)
{
	return -ENOSYS;
}

static inline int
reset_control_deassert(struct reset_control *reset)
{
	return -ENOSYS;
}

/******************************************************************************
 * devres
 *****************************************************************************/

#define devm_clk_get clk_get
#define devm_regulator_get regulator_get
#define devm_reset_control_get reset_control_get

/******************************************************************************
 * tegra
 *****************************************************************************/
struct tegra_sku_info {
	int gpu_speedo_value;
	int gpu_speedo_id;
};

extern struct tegra_sku_info tegra_sku_info;

#define TEGRA_POWERGATE_3D 1

static inline int
tegra_powergate_remove_clamping(int id)
{
	return -ENOSYS;
}

static inline int
tegra_fuse_readl(unsigned long offset, u32 *value)
{
	*value = 0;
	return -ENOSYS;
}

/******************************************************************************
 * endianness (cont'd)
 *****************************************************************************/

#if __BYTE_ORDER == __LITTLE_ENDIAN
#undef __BIG_ENDIAN
#endif

#endif
