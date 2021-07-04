with open('map') as f:
    map_pices =  [l.strip() for l in f.readlines() if l.strip()]

h = len(map_pices)
w = len(map_pices[0]) if len(set(len(p) for p in map_pices)) == 1 else None

# import ipdb; ipdb.set_trace()

if not w or h < 2:
    print("error in map")
    exit(1)

print('#define MAP_WIDTH %d' % w)
print('#define MAP_HEIGHT %d' % h)
print()
print('const byte lvl_map[MAP_HEIGHT][MAP_WIDTH] PROGMEM = {')
for pice in map_pices:
    vals = ', '.join(pice)
    print('\t{%s},' % vals)
print('};')



