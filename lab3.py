import numpy as np
import matplotlib.pyplot as plt

# Initial points of triangle ABC
triangle = np.array([[0, 0], [1, 0], [0, 1]])

# Function to plot triangle
def plot_triangle(pts, color='b'):
    plt.plot([pts[0, 0], pts[1, 0]], [pts[0, 1], pts[1, 1]], color)
    plt.plot([pts[1, 0], pts[2, 0]], [pts[1, 1], pts[2, 1]], color)
    plt.plot([pts[2, 0], pts[0, 0]], [pts[2, 1], pts[0, 1]], color)

# Transformation functions
def translate(pts, dx, dy):
    return pts + np.array([dx, dy])

def scale(pts, x0, y0, sx, sy):
    return (pts - np.array([x0, y0])) * np.array([sx, sy]) + np.array([x0, y0])

def rotate(pts, x0, y0, angle_deg):
    angle_rad = np.radians(angle_deg)
    rotation_matrix = np.array([
        [np.cos(angle_rad), -np.sin(angle_rad)],
        [np.sin(angle_rad), np.cos(angle_rad)]
    ])
    return (pts - np.array([x0, y0])) @ rotation_matrix.T + np.array([x0, y0])

def reflect(pts, a, b):
    reflected_pts = []
    for x, y in pts:
        d = (x + (y - b) * a) / (1 + a ** 2)
        xr = 2 * d - x
        yr = 2 * d * a - y + 2 * b
        reflected_pts.append([xr, yr])
    return np.array(reflected_pts)

# Event handler for mouse clicks
points = []  # to store click coordinates

def on_click(event):
    global points
    if event.button == 1:  # Left click
        points.append((event.xdata, event.ydata))
        if len(points) == 2:
            # Example: perform translation based on 2 points (for vector dx, dy)
            dx, dy = points[1][0] - points[0][0], points[1][1] - points[0][1]
            transformed = translate(triangle, dx, dy)
            plot_triangle(transformed, 'g')  # Plot in green
            plt.draw()
            points = []  # Reset for next transformation

# Setup plot
fig, ax = plt.subplots()
plot_triangle(triangle, 'b')  # Original in blue
plt.axis('equal')
cid = fig.canvas.mpl_connect('button_press_event', on_click)
plt.show()
