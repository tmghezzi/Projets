import sublime, sublime_plugin
from xml.dom.minidom import parse
import xml.dom.minidom

def textPanel(self,edit,strDescription):
	self.output_view = self.view.window().get_output_panel("textarea")
	self.view.window().run_command("show_panel", {"panel": "output.textarea"})
	self.output_view.set_read_only(False)
	edit = self.output_view.begin_edit()
	#malloc SYSCTL_OUT
	self.output_view.insert(edit, self.output_view.size(), strDescription)
	self.output_view.end_edit(edit)
	self.output_view.set_read_only(True)
	# open an input box for some user input
	#self.view.window().show_input_panel("Please enter a comment:", '',None, None, None)


def findDescription(functionName):
	strDescription = ""
	DOMTree = xml.dom.minidom.parse("functionDB.xml")
	collection = DOMTree.documentElement
	functions = collection.getElementsByTagName("elementName")

	for elementName in elementNames:
		if elementName.hasAttribute("title"):
			print "title: %s" %elementName.getAttribute("title")
			if functionName == elementName.getAttribute("title"):
				strFirst = str(elementName.getElementsByTagName('element_declaration')[0].childNodes[0].data)
				strSecond = str(elementName.getElementsByTagName('description')[0].childNodes[0].data)
				strDescription = "Function: {0} \nComments: {1}".format(strFirst, strSecond)
	return strDescription

class OpenInfoCommand(sublime_plugin.TextCommand):
	def run(self,edit):
		selection = ""
		for region in self.view.sel():
			selection += self.view.substr(region)
		strDescription = ""
		strDescription = findDescription(selection)
		if strDescription == "":
			textPanel(self,edit,"No found")
		else:
		#sublime.error_message(strDescription)
			textPanel(self,edit,strDescription)

