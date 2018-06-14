
#ifndef __JEMALLOC_EXTENT_HOOKS_H
#define __JEMALLOC_EXTENT_HOOKS_H 1


#ifdef __cplusplus
extern "C" {
#endif

typedef struct extent_hooks_s extent_hooks_t;


typedef void *(extent_alloc_t)(extent_hooks_t *extent_hooks, void *new_addr, size_t size,
    size_t alignment, bool *zero, bool *commit, unsigned arena_ind);

typedef bool (extent_dalloc_t)(extent_hooks_t *extent_hooks, void *addr, size_t size,
     bool committed, unsigned arena_ind);

typedef void (extent_destroy_t)(extent_hooks_t *extent_hooks, void *addr, size_t size,
      bool committed, unsigned arena_ind);

typedef bool (extent_commit_t)(extent_hooks_t *extent_hooks, void *addr, size_t size,
     size_t offset, size_t length, unsigned arena_ind);

typedef bool (extent_decommit_t)(extent_hooks_t *extent_hooks, void *addr, size_t size,
     size_t offset, size_t length, unsigned arena_ind);

typedef bool (extent_purge_t)(extent_hooks_t *extent_hooks, void *addr, size_t size,
     size_t offset, size_t length, unsigned arena_ind);

typedef bool (extent_split_t)(extent_hooks_t *extent_hooks, void *addr, size_t size,
     size_t size_a, size_t size_b, bool committed, unsigned arena_ind);

typedef bool (extent_merge_t)(extent_hooks_t *extent_hooks, void *addr_a, size_t size_a,
    void *addr_b, size_t size_b, bool committed, unsigned arena_ind);

struct extent_hooks_s {
	extent_alloc_t		*alloc;
	extent_dalloc_t		*dalloc;
	extent_destroy_t	*destroy;
	extent_commit_t		*commit;
	extent_decommit_t	*decommit;
	extent_purge_t		*purge_lazy;
	extent_purge_t		*purge_forced;
	extent_split_t		*split;
	extent_merge_t		*merge;
};

#ifdef __cplusplus
}
#endif

#endif /** __JEMALLOC_EXTENT_HOOKS_H */
