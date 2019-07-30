#!/usr/bin/env python3
import sys
from zlib import decompress
from struct import unpack_from
from scapy.all import rdpcap, TCP
import pygame

pygame.init()

SIZEX = 125
SIZEZ = 750
gameDisplay = pygame.display.set_mode((SIZEZ, SIZEX))
pygame.display.set_caption('MC')

positions = []


def is_ctos(x):
    return x.dport == 25565


def varint(d):
    n = 0
    r = 0
    while True:
        b = d[n]
        v = b & 0b01111111
        r |= (v << (7 * n))
        n += 1
        assert n <= 5
        if (b & 0b10000000) == 0:
            break
    return (r, n)


def keep_alive(d):
    id = unpack_from('>q', d, 0)[0]
    return 'Keep Alive. ID: {}'.format(id)


def player_position(d):
    x = unpack_from('>d', d, 0)[0]
    y = unpack_from('>d', d, 8)[0]
    z = unpack_from('>d', d, 16)[0]
    g = bool(d[24])
    positions.append((x, y, z, g))
    return 'Player Position. x: {}, y: {}, z: {}, g: {}'\
        .format(x, y, z, g)


def player_position_and_look(d):
    x = unpack_from('>d', d, 0)[0]
    y = unpack_from('>d', d, 8)[0]
    z = unpack_from('>d', d, 16)[0]
    g = bool(d[32])
    positions.append((x, y, z, g))
    return 'Player Position And Look. x: {}, y: {}, z: {}, g: {}'\
        .format(x, y, z, g)


def player_look(x): return 'Player Look'


def entity_action(x): return 'Entity Action'


def animation(x): return 'Animation'


def player_block_placement(x): return 'Player Block Placement'


client_cmds = {
    0x0e: keep_alive,
    0x10: player_position,
    0x11: player_position_and_look,
    0x12: player_look,
    0x19: entity_action,
    0x27: animation,
    0x29: player_block_placement,
}


def block_change(d): return 'Block Change'


def boss_bar(d): return 'Boss Bar'


def steer_vehicle(d): return 'Steer Vehicle'


def unload_chunk(d):
    x = unpack_from('>I', d, 0)[0]
    z = unpack_from('>I', d, 4)[0]
    return 'Unload Chunk. x: {}, z: {}'.format(x, z)


def keep_alive(d):
    id = unpack_from('>q', d, 0)[0]
    return 'Keep Alive. ID: {}'.format(id)


def chunk_data(d):
    x = unpack_from('>I', d, 0)[0]
    z = unpack_from('>I', d, 4)[0]
    return 'Chunk Data. x: {}, z: {}'.format(x, z)


def player_info(d):
    (action, n) = varint(d)
    return 'Player Info. Action: {}'.format(action)


def entity_metadata(d): return 'Entity Metadata.'


def entity_velocity(d): return 'Entity Velocity'


def time_update(d):
    w = unpack_from('>Q', d, 0)[0]
    t = unpack_from('>Q', d, 8)[0]
    return 'Time Update. World Age {}, Time of Day {}'.format(w, t)


def entity_properties(d): return 'Entity Properties.'


server_cmds = {
    0x0b: block_change,
    0x1f: unload_chunk,
    0x21: keep_alive,
    0x22: chunk_data,
    0x30: player_info,
    0x3f: entity_metadata,
    0x4a: time_update,
    0x52: entity_properties,
}

a = rdpcap("dump")
p = b''
for i, x in enumerate(a):
    if not len(x[TCP].payload):
        continue
    p += bytes(x[TCP].payload)
    while len(p) > 0 and len(p) >= p[0] + 1:
        (l, n1) = varint(p[0:])
        (l2, n2) = varint(p[n1:])
        if l2:
            d = decompress(p[n1+n2:n1+n2+l])
        else:
            d = p[2:l+1]
        if is_ctos(x):
            print('C -> S {}'.format(client_cmds[d[0]](d[1:])))
        else:
            print('S -> C {}'.format(server_cmds[d[0]](d[1:])))
        p = p[l+1:]

mx, mz = 10000, 10000
for x, y, z, g in positions:
    mx = min(x, mx)
    mz = min(z, mz)
c = [(x - mx, y, z - mz, g) for x, y, z, g in positions]
mx, mz = 0, 0
for x, _, z, _ in c:
    mx = max(x, mx)
    mz = max(z, mz)

clock = pygame.time.Clock()
surface = pygame.display.get_surface()
for x, y, z, g in c:
    x = int(50 + (mx - x) * (SIZEX - 100) / mx)
    z = int(50 + z * (SIZEZ - 100) / mz)
    surface.set_at((z, x), (255 if g else 0, 255 if y == 4.0 else 0, 255))
    pygame.display.update()
while True:
    clock.tick(100)
    pygame.display.update()
    for e in pygame.event.get():
        if e.type == pygame.KEYDOWN:
            if e.key == pygame.K_q or e.key == pygame.K_ESCAPE:
                pygame.quit()
                sys.exit()
