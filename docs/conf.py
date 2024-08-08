project = "Units"

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = [
    "breathe",
    "myst_parser",
    "sphinx_copybutton",
    "sphinx.ext.autosectionlabel",
    "sphinx.ext.todo",
]

templates_path = ["_templates"]
exclude_patterns = ["_build", "Thumbs.db", ".DS_Store"]


# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = "furo"

html_theme_options = {
    "source_repository": "https://github.com/lemlib/lemlib/",
    "source_branch": "master",
    "source_directory": "docs/",
    "light_css_variables": {
        "color-brand-primary": "#00C852",
        "color-brand-content": "#00C852",
    },
    "dark_css_variables": {
        "color-brand-primary": "#00C852",
        "color-brand-content": "#00C852",
    },
}

html_static_path = ["_static"]


breathe_projects = {"Units": "xml/"}

breathe_projects_source = {"LemLib": ("../", ["include/units"])}

breathe_default_project = "Units"

myst_enable_extensions = [
    "amsmath",
    "attrs_inline",
    "colon_fence",
    "deflist",
    "dollarmath",
    "fieldlist",
    "html_admonition",
    "html_image",
    "linkify",
    "replacements",
    "smartquotes",
    "strikethrough",
    "substitution",
    "tasklist",
]


# Run doxygen for the readthedocs build

import subprocess, os

read_the_docs_build = os.environ.get("READTHEDOCS", None) == "True"

if read_the_docs_build:
    subprocess.call("cd ../doxygen; doxygen", shell=True)
