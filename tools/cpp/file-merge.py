import re
import sys

class FileMergerCpp():

	def __init__(self):
		print("=== Merge file tool CPP ===\n")

		self.PATH_TO_MAIN_FILE = "../../code-base/cpp/main.cpp"
		self.MAIN_FILENAME = ""
		self.INCLUDE_ROOT = ""
		self.RES_FILENAME = ""

		self.std_libraries = {}
		self.user_files = {}
		self.user_files_ordered = []

	# Handling args

	def init(self):

		if len(sys.argv) > 1:
			self.PATH_TO_MAIN_FILE = sys.argv[1]
	
		self.MAIN_FILENAME = self.PATH_TO_MAIN_FILE.split("/")[-1]

		if len(sys.argv) > 2:
			self.INCLUDE_ROOT = sys.argv[2]
		else:
			self.INCLUDE_ROOT = self.PATH_TO_MAIN_FILE[0:-len( self.MAIN_FILENAME )]

		if len(sys.argv) > 3:
			self.RES_FILENAME = sys.argv[3]
		else:
			self.RES_FILENAME = "merge.cpp"
		
		print( "Merged from file:\t", self.MAIN_FILENAME )
		print( "Includes root:\t\t", self.INCLUDE_ROOT )
		print( "Output:\t\t\t", self.RES_FILENAME )
		print()

	# Check if in this line of code, there is an std include
	def checkStdMatch( self, line ):
		match = re.search( "<.*>", line )
		if match is None: return False
	
		libs = match.group(0).replace("<", " ").replace(">", " " )
		for lib in libs.split():
			self.std_libraries[lib] = True
		return True


	# Check if in this line of code there is a file include
	def checkFileIncludeMatch( self, line, path_from_root ):

		match = re.search( "\".*\"", line )
		if match is None: return False

		includes = match.group(0).replace("\"", " ")
		for include in includes.split():
		
			split_clude = include.split("/")
			local_filename = split_clude[-1]
			local_path_from_root = path_from_root + "/".join( split_clude[0:-1] ) + ("/" if len(split_clude) > 1 else "")

			#print( "LPFR", local_path_from_root, "LF", local_filename )
			if self.getIncludeStack( local_path_from_root, local_filename ):
				real_path = local_path_from_root + local_filename
				if real_path not in self.user_files:
					self.user_files_ordered.append( real_path )
					self.user_files[ real_path ] = True

			if self.getIncludeStack( "", include ):
				if include not in self.user_files:
					self.user_files_ordered.append( include )
					self.user_files[ include ] = True

		return True

	# Get the includes of a file recursively
	def getIncludeStack( self, path, filename ):
	
		try:
			f = open( self.INCLUDE_ROOT + path + filename )
		except FileNotFoundError:
			return False

		lines = f.readlines()
		for line in lines: 

			if "#include" not in line: continue
		
			# Check for std includes
			self.checkStdMatch( line )
			self.checkFileIncludeMatch( line, path )

		return True


	def proceed( self ):
		self.getIncludeStack( "", self.PATH_TO_MAIN_FILE )
		self.user_files_ordered.append( self.PATH_TO_MAIN_FILE )
		self.user_files[ self.PATH_TO_MAIN_FILE ] = True

		res_file = open( self.RES_FILENAME, "w+")

		print( "Required standard libs:")
		for lib in self.std_libraries:
			print( "-", lib )

		print()

		print( "Files imported:")
		for user_file in self.user_files_ordered:
			print( "-", user_file )

		for lib in self.std_libraries:
			res_file.write( "#include <" + lib + ">\n" )

		for user_file in self.user_files_ordered:
			f = open( self.INCLUDE_ROOT + user_file, "r" )
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

		res_file.close( )

if __name__ == "__main__":
	fmc = FileMergerCpp()
	fmc.init()
	fmc.proceed()