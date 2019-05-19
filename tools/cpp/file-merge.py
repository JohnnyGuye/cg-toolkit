import re
import sys







print("=== Merge file tool ===\n")

path_to_file = "../../code-base/cpp/main.cpp"
filename = ""
INCLUDE_ROOT = ""

# Handling args

if len(sys.argv) > 1:
	path_to_file = sys.argv[1]
	
filename = path_to_file.split("/")[-1]

if len(sys.argv) > 2:
	INCLUDE_ROOT = sys.argv[2]
else:
	INCLUDE_ROOT = path_to_file[0:-len(filename)]

	
print( "Merged from file:\t", filename )
print( "Includes root:\t\t", INCLUDE_ROOT )

res_filename = "merge.cpp"
res_file = open(res_filename, "w+")


std_libraries = {}
user_files = {}
user_files_ordered = []

# Check if in this line of code, there is an std include
def checkStdMatch( line ):
	match = re.search( "<.*>", line )
	if match is None: return False
	
	libs = match.group(0).replace("<", " ").replace(">", " " )
	for lib in libs.split():
		std_libraries[lib] = True
	return True


# Check if in this line of code there is a file include
def checkFileIncludeMatch( line, path_from_root ):

	match = re.search( "\".*\"", line )
	if match is None: return False

	includes = match.group(0).replace("\"", " ")
	for include in includes.split():
		
		split_clude = include.split("/")
		local_filename = split_clude[-1]
		local_path_from_root = path_from_root + "/".join( split_clude[0:-1] ) + ("/" if len(split_clude) > 1 else "")

		#print( "LPFR", local_path_from_root, "LF", local_filename )
		if getIncludeStack( local_path_from_root, local_filename ):
			real_path = local_path_from_root + local_filename
			if real_path not in user_files:
				user_files_ordered.append( real_path )
				user_files[ real_path ] = True

		if getIncludeStack( "", include ):
			if include not in user_files:
				user_files_ordered.append( include )
				user_files[ include ] = True

	return True

# Get the includes of a file recursively
def getIncludeStack( path, filename ):
	
	try:
		f = open( INCLUDE_ROOT + path + filename )
	except FileNotFoundError:
		return False

	lines = f.readlines()
	for line in lines: 

		if "#include" not in line: continue
		
		# Check for std includes
		checkStdMatch( line )
		checkFileIncludeMatch( line, path )

	return True

getIncludeStack( "", filename )
user_files_ordered.append( filename )
user_files[filename] = True

print( "Required standard libs:")
for lib in std_libraries:
	print( "-", lib )

print()

print( "Files imported:")
for user_file in user_files_ordered:
	print( "-", user_file )

for lib in std_libraries:
	res_file.write( "#include <" + lib + ">\n" )

for user_file in user_files_ordered:
	f = open( INCLUDE_ROOT + user_file, "r" )
	lines = f.readlines()
	includedOnce = False
	for line in lines:
		if "#include" in line: continue
		if "#pragma once" in line: continue

		if line.strip() == "" and not includedOnce: continue

		if not includedOnce:
			res_file.write( "\n\n// Merge tool " + ("=" * 49) + "\n" )
			res_file.write( "// Imported from the file: " + user_file + "\n" )
			res_file.write( "// " + ("=" * 60) + "\n\n" )
	
		includedOnce = True
		res_file.write( line )
