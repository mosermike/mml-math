# Configuration file for the Sphinx documentation builder.

# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'mml-math'
copyright = '2024, Mike Moser'
author = 'Mike Moser'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

import sys
sys.path.append("/home/mike/Downloads/breathe/")

templates_path = ['_templates']
exclude_patterns = []

extensions = [
    'sphinx.ext.autodoc',
    'sphinx.ext.doctest',
    'sphinx.ext.viewcode',
    'sphinx.ext.imgmath', 
    'sphinx.ext.todo',
    'breathe',
    'sphinx_math_dollar',
    'sphinx.ext.napoleon',
    'numpydoc',

]

"""
def linkcode_resolve(domain, info):
    if domain != 'py':
        return None
    if not info['module']:
        return None
    filename = info['module'].replace('.', '/')
    return "https://gitlab.moser.mywire.org/moser/mml/-/blob/main/src/%s.cpp" % filename
"""

import subprocess
subprocess.call('make clean', shell=True)
subprocess.call('cd ../../ ; doxygen docs/doxygen/doxygen.conf', shell=True)

breathe_projects = { "mml-math": "../doxygen/xml/" }
breathe_default_project = "mml-math"

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = ''
html_static_path = ['_static']

html_theme = 'pydata_sphinx_theme'
