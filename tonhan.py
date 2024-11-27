import sys

def convert_obj_to_custom_format(obj_file, output_file):
    with open(obj_file, 'r') as obj:
        lines = obj.readlines()
    
    vertices = []  
    faces = []   
    for line in lines:
        line = line.strip()
        if line.startswith('#'):
            continue
        
        if line.startswith('v '):
            parts = line.split()
            x, y, z = map(float, parts[1:])
            vertices.append((x, y, z))
        
        elif line.startswith('f '):
            parts = line.split()
            face_indices = [int(p.split('/')[0]) - 1 for p in parts[1:]]
            faces.append(face_indices)
    
    with open(output_file, 'w') as out:
        out.write(f"{len(faces)}\n")
        
        for face in faces:
            out.write(f"{len(face)} 1.0 0.0 0.0\n")
            for vertex_index in face:
                x, y, z = vertices[vertex_index]
                out.write(f"{x} {y} {z}\n")

if len(sys.argv) != 2:
    print("Usage: python tonhan.py <input.obj>")
    sys.exit(1)

obj_file = sys.argv[1]
output_file = obj_file.replace('.obj', '.nhan')

convert_obj_to_custom_format(obj_file, output_file)
