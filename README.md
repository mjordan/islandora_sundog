# Islandora Sundog

Experimental module that adds fields to Solr by bypassing Fedora GSearch. The motivation for doing this is that adding custom fields to Solr is typically done by modifying the XSLT stylesheets invoked by GSearch. This requires access to the server GSearch is running on, and also... modifying XSLT stylesheets on the server GSearch is running on. This module implements an alternative way of adding additional fields to Solr, for example, to customize searching and metadata display.

# Background

It is possible to update and add specific fields to Solr documents using HTTP calls to Solr's `/update` endpoint, such as:

```
curl -v http://localhost:8080/solr/update -H 'Content-type:application/json' -d @test.json
```

where the file test.json contains:

```json
[
 {"PID"       : "newpdf:5",
  "dc.description"   : {"set":"I have been updated."}
 }
]
```

Add new fields uses a similar operation. Significantly, 

1. it is possible to add entirely new fields that don't need to be defined in your Solr schema, and
1. these new fields show up in Islandora's user interfaces for defining custom metadtata display and advanced search options.

For example, with this test.json:

```json
[
 {"PID"       : "newpdf:5",
  "footest"   : {"set":"Is this field showing up in Solr?"}
 }
]
```

This shows up in the Solr document for newpdf:5:

```xml
 <arr name="footest">
      <str>Is this field showing up in Solr?</str>
 </arr>
```

However, there is a problem - this technique only works if the Solr document corresponding to an Islandora object already exists. Indexing Solr via GSearch after object ingestion or update takes a few seconds, so we we need to wait until GSearch has finished before we can add or update fields in a Solr document using Solr's `/update` HTTP endpoint. To work around this problem, we fire the HTTP request to `/update` in a background process that waits a specific amount of time (say 10 seconds), invisibly to the end user, after object/datastream ingest or update.

## Requirements

* [Islandora](https://github.com/Islandora/islandora)
* [Background Process](https://www.drupal.org/project/background_process)

## Usage

This module is currently highly experimental. All you need to do is enable it, there are no configuration options or user interface. However, those will come soon, once the basic technique this module illustrates is more robust.

## To do

* Add some useful examples of new Solr fields
* Start thinking about a UI for allowing Islandora admins to control what goes in their custom Solr fields

## Maintainer

* [Mark Jordan](https://github.com/mjordan)

## Development and feedback

Pull requests are welcome, as are use cases and suggestions.

## Further Development

## License

 [GPLv3](http://www.gnu.org/licenses/gpl-3.0.txt)
