#!/usr/bin/python

"""
Scala Project Generator for SBT
version 0.0.1

Alexander Pohl
Programming and Modeling Languages
Institute for Informatics
Ludwig-Maximilian University Munich
"""

import sys, os

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

project = ""
currentPath = os.getcwd()

projectStructure = [
  os.path.join('src', 'main', 'resources'),
  os.path.join('src', 'main', 'scala'),
  os.path.join('src', 'main', 'java'),
  os.path.join('src', 'test', 'resources'),
  os.path.join('src', 'test', 'scala'),
  os.path.join('src', 'test', 'java'),
  'lib',
  'project',
  'target'
]


def writeBuildFile(path, project, scalaVersion):
  p = os.path.join(path, project, "build.sbt")
  buildFile = open(p, "w")
  buildFile.write('''name := "{0}"

version := "0.1.0-SNAPSHOT"

scalaVersion := "{1}"

libraryDependencies ++= Seq(
  "org.scalatest" % "scalatest_2.11" % "2.2.4" % "test", 
  "org.scalacheck" %% "scalacheck" % "1.12.5" % "test",
  "org.scalamock" %% "scalamock-scalatest-support" % "3.2" % "test"
)

scalacOptions in Test ++= Seq("-Yrangepos")

'''.format(project, scalaVersion))
  buildFile.close() 

def writePluginFile(path, project):
  p = os.path.join(path, project, "project", "plugins.sbt")
  pluginFile = open(p, "w")
  pluginFile.write('''resolvers += Resolver.sonatypeRepo("public")

resolvers += Classpaths.typesafeResolver

addSbtPlugin("com.typesafe.sbteclipse" % "sbteclipse-plugin" % "2.5.0")

addSbtPlugin("com.github.mpeltonen" % "sbt-idea" % "1.6.0")

''')
  pluginFile.close()

def writeGitIgnore(path, project):
  p = os.path.join(path, project, ".gitignore")
  gitignoreFile = open(p, "w")
  gitignoreFile.write('''
target/
.idea_modules/
.DS_Store
.classpath
.project
*.log
*.*~
''')


if len(sys.argv) > 1:
  project = sys.argv[1]

overwriteProject = raw_input("Project Name [{0}]: ".format(project))
if overwriteProject != "":
  project = overwriteProject.strip()
  
print("creating " + os.path.join(currentPath, project))
try:
  for d in projectStructure:
    path = os.path.join(currentPath, project, d)
    print("    creating dir {0}".format(path))
    os.makedirs(path)
  print ("    writing build file")
  writeBuildFile(currentPath, project, "2.11.7")
  print ("    writing plugins file")
  writePluginFile(currentPath, project)
  print ("    writing gitignore file")
  writeGitIgnore(currentPath, project)
  print bcolors.OKGREEN + "SUCCESS!" + bcolors.ENDC
except:
  print(bcolors.FAIL + "ERROR: something went wrong with {0}".format(os.path.join(currentPath, project)) + bcolors.ENDC)
