# Islandora Sundog

Experimental module that adds fields to Solr by bypassing Fedora GSearch.

# Background

## The problem

Adding custom fields to Solr for the purpose of customizing search and metadata display is typically done by modifying the XSLT stylesheets invoked by GSearch, or by adding new stylesheets. This poses considerable challenges to many Islandora admins because it requires access to the server GSearch is running on, and it requires decent XSLT chops. Islandora Sundog aims to implement an alternative way of adding locally-defined fields to Solr via a graphical user interface.

## The technical solution

It is possible to [update and add specific fields](https://cwiki.apache.org/confluence/display/solr/Updating+Parts+of+Documents) to Solr documents using calls to Solr's `/update` HTTP endpoint, such as:

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

Adding new fields uses a similar operation. Significantly, 

1. it is possible to add entirely new fields that don't need to be defined in your Solr schema, and
1. these new fields show up in Islandora's user interfaces for defining custom metadata display and advanced search options.

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

# Challenges

This technique for adding data to an Islandora's Solr index poses a couple of challenges:

* it only works if the Solr document corresponding to an Islandora object already exists. Indexing Solr via GSearch after object ingestion or modification can take a few seconds, so we cannot use Islandora's hook_islandora_object_ingested(), hook_islandora_datastream_modified(), etc. to add our data to Solr. Therefore, we need to wait a short while until GSearch has finished before we add fields in a Solr document using Solr's `/update` HTTP endpoint. To work around this problem, we fire the HTTP request to `/update` in a background process that waits a specific amount of time (say 10 seconds), invisibly to the end user, after object/datastream ingest or update.
* we can only add fields of the type "string" to Solr, and not "text", "int", "boolean", etc. This means that Solr does no tokenization or other types of processing on the data. So for example, if we want our data to be normalized to lowercase, we need to do it ourselves before we add it to Solr. It is posible to add multivalued fields.
* for it to serve as a viable alternative to manually modifying GSearch's XSLT stylesheets, we will need to provide a user interface that is both straight forward and flexible.

# Requirements

* [Islandora](https://github.com/Islandora/islandora)
* [Background Process](https://www.drupal.org/project/background_process)
  * And its dependency [Progress](https://www.drupal.org/project/progress)

# Usage

This module is currently experimental and currently is intended mainly to demonstrate that adding custom fields to Solr is viable.

It is also intended to provide an opportunity to explore how a user interface for managing these custom fields would work. Currently, options for determining the field labels of two custom fields is available. The content of these fields is not configurable (one is the upper-cased version of the object's label, and the other is the object's PID namespace). To try these fields out:

1. Go to the admin form at `admin/islandora/tools/sundog`. Enter the field labels you want for your two custom fields:
  * ![custom field labels](images/config.png)
1. Save your settings.
1. Trigger the addition of these two fields to an object's Solr document by editing a datastream (MODS, for example).
  * Custom fields that are configured will be added to Solr documents for objects that are newly ingested, objects whose properties (label, state, etc.) are changed, datastreams that are newly ingested, and datastreams whose content or properties are changed.
1. Visit your local Solr (for example, http://localhost:8080/solr/#/collection1/query) to see the new fields. Query for the PID of the object you modified by entering the following in the query field: `PID:mypid\:1234` (where "mypid:1234" is the PID you want to query). Near the bottom of the results, you should see your custom fields:
  * ![custom fields in Solr](images/solr_document.png)
1. To see the custom fields show up in the Islandora Solr module's metadata display configuration tool, try to add one of your custom fields to a metadata display:
  * ![custom fields in Solr](images/add_custom_field_to_display.png)

# Further development

* Add more useful examples of new Solr fields (e.g., multivalued fields)
* Develop some use cases for adding custom fields to Islandora's Solr index
* Develop an effective UI for allowing Islandora admins to control what goes in their custom Solr fields
* Define hooks that will allow other modules to generate custom Solr fields
* Think about how to add custom fields to Sorl for more than one object (e.g., via a drush script or a batch UI)

# Maintainer

* [Mark Jordan](https://github.com/mjordan)

# Development and feedback

Pull requests are welcome, as are use cases and suggestions.

# License

 [GPLv3](http://www.gnu.org/licenses/gpl-3.0.txt)
