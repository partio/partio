--------------------------------------------------------------------------------

# What is partio?

Partio is a small security focused data sharing program. It will be able to
handle chats and file transfers in the beginning but anything will be possible
be it voice chat or streaming since the focus is secure information sharing
whatever type it is.


--------------------------------------------------------------------------------

# -- TODO --

- Write configfile parser lib

  *This is almost finished, all it needs is the fileparser::getOneOption to work
   as expected, some way of knowing when there are no more options.

- Write network lib

- Write xml lib

- Implement XMPP

- Implement SSL

- Implement AES

- Implement Threading with workers

- Do we need an api?

- Definitely need scaling i.e. server to server talking

- Document everything

--------------------------------------------------------------------------------

# Librarys used

It might work with older or newer versions but it is developed with the specified one

* Botan version 1.10.5

--------------------------------------------------------------------------------

# Partio versioning

### Example: (x.y.z)


### Major [x]

- Major feature changes

- Redesigns


### Minor [y]

- New features

- Major bugfixses

- Enhancements

  * faster algorithms for example


### Maintenance [z]

- Security updates

- Minor bugs

- Minor api changes

- Other minor changes

--------------------------------------------------------------------------------

# Git branching conventions:


### Master branch [master]

This it the main release branch, it will only contain "finished" releases


### Hotfix branch [hotfix]

> Branch off: [master]

> Merge to: [master]

This branch is for emergency fixses to master branch


### Release branch [rl-{version}]

> Branch off: [dev]

> Merge to: [master]

This branch is a feature freeze bugfix only branch used to stabilize releases


### Development branch [dev]

> Branch off: --

> Merge to: [rl-{version}]

This branch is the main branch for development, considered dangerously unstable


### Feature branches [fet-{feture name}]

> Branch off: [dev]

> Merge to: [dev]

These branches should be used for creating new features


### Issue branches [iss-{issue id}]

> Branch off: [dev]

> Merge to: [dev]

Branches used for fixing bugs from our issue tracker where the id can be found

--------------------------------------------------------------------------------
