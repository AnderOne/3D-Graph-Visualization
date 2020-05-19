import open3d as o3d
import numpy as np
import sys

num_vert, num_edge, *edge = map(int, open(sys.argv[1], 'r').read().split())
edge = set([(edge[2 * i], edge[2 * i + 1]) for i in range(num_edge)])

vert = [float(v) for v in open(sys.argv[2], 'r').read().split()]
vert = tuple(zip(vert[0 :: 3], vert[1 :: 3], vert[2 :: 3]))

point_cloud = o3d.geometry.PointCloud(
	points = o3d.utility.Vector3dVector(vert)
)

point_cloud.colors = o3d.utility.Vector3dVector([(0, 0, 1) for i in vert])

line_set = o3d.geometry.LineSet(
	points = o3d.utility.Vector3dVector(vert),
	lines = o3d.utility.Vector2iVector(edge)
)

line_set.colors = o3d.utility.Vector3dVector([(1, 0, 0) for i in edge])

o3d.visualization.draw_geometries(
	[point_cloud, line_set]
)
