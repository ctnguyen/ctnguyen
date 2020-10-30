## Opensource documentation

This is an example of how to document a opensource repository on github. There are two different tools, using the same directories structure so it is possible to have the same structure working for both :

- [github pages](https://pages.github.com/)
- [mkdocs](https://www.mkdocs.org/)

They both use the markdown files to build the html content, with the _same directories structure_, i.e all `*.md` files are in the `docs` directory. Precisely

**github pages** directory structure
```
Root repo
    |---docs
    |    |---index.md
    |    |---My_Page_1.md
    |    |---My_Page_2.md
    |    |---...
    |    |---My_Page_N.md
```
**mkdocs** directory structure
```
Root repo
    |---docs
    |    |---index.md
    |    |---My_Page_1.md
    |    |---My_Page_2.md
    |    |---...
    |    |---My_Page_N.md
    |---mkdocs.yml
```
  Where `mkdocs.yml` is the configuration file that `mkdocs` will use to build the html content.

To make it works on _github pages_, the first thing to do is to make the repository(project) opensource. Then go to the repository setting, scroll down to the section _Github Pages_, select source as _master_ branch, directory _docs_, then save it. After saving, Git will say _Your site is ready to be published at_ http://<user_name>.github.io/<repo_name>/. 

`mkdocs` is another approach, using the same documentation content, i.e `*.md` files. It build the static `html` content locally, and it is free to publish anywhere. For more detail of how it work, see [mkdocs setup](mkdocs_demo.md)