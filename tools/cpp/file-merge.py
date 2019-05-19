import re








print("=== Merge file tool ===\n")

path_to_file = "../../code-base/cpp/main.cpp"
filename = path_to_file.split("/")[-1]
path_to_root = path_to_file[0:-len(filename)]

print( path_to_root, filename )

res_filename = "merge.cpp"
res_file = open(res_filename, "w+")


std_libraries = {}
user_files = {}
user_files_ordered = []

def getIncludeStack( root, filename ):
	
	f = open( root + filename, "r")
	lines = f.readlines()
	for line in lines:
		if "#include" not in line: continue

		match = re.search( "<.*>", line )
		if match is not None:
			libs = match.group(0).replace("<", " ").replace(">", " ")
			#print( "Add to std libs", libs.split( ) )
			for lib in libs.split():
				std_libraries[lib] = True
		else:
			match = re.search( "\".*\"", line )
			if match is not None:
				libs = match.group(0).replace("\"", " ").replace("\"", " ")
				#print( "Add to std libs", libs.split( ) )
				for lib in libs.split():
					if lib not in user_files:
						getIncludeStack( root, lib )
						user_files_ordered.append( lib )
					user_files[lib] = True
	f.close()


getIncludeStack( path_to_root, filename )
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
	f = open( path_to_root + user_file, "r" )
	lines = f.readlines()
	includedOnce = False
	for line in lines:
		if "#include" in line: continue
		if "#pragma once" in line: continue

		if line.strip() == "" and not includedOnce: continue

		if not includedOnce:
			res_file.write( "\n\n//" + ("=" * 60) + "\n" )
			res_file.write( "// Imported from the file: " + user_file + "\n" )
			res_file.write( "//" + ("=" * 60) + "\n\n" )
	
		includedOnce = True
		res_file.write( line )
