The following will update the dc.description field in the Solr document for PID newpdf:5:

```
curl -v http://localhost:8080/solr/update -H 'Content-type:application/json' -d @test.json
```

where the file test.json contains:

```json
[
 {"PID"       : "newpdf:5",
  "dc.description"   : {"set":"I have been updated - correct?."}
 }
]
```


Perhaps more importantly, you can add entirely new fields that don't need to be defined in your schema to your Solr documents (and these new fields show up in the custom metadtata display and advanced search options - !!). With this test.json:

```json
[
 {"PID"       : "newpdf:5",
  "marktest"   : {"set":"Is this field showing up in Solr?"}
 }
]
```

This shows up in my Solr document:

```xml
 <arr name="marktest">
      <str>Is this field showing up in Solr?</str>
 </arr>
```


What this means is, it is possible to do some post-processing to tune your Solr index for better searching and display using custom fields. Probably the best place to issue these REST commands to Solr (via Islandora's Solr query API) would be in object and datastream ingested and modified hooks, although we need to confirm that the Solr document exists when the hook fires, or that changes to the Solr document aren't overwritten by a gsearch-based update, which I believe deletes and then regenerates the solr document.

This is just a proof of concept, but I'm definitely going to play with it some more. There's still the question of a user interface to configure localizations to Solr, but at least we don't need to futz with gsearch's XSLTs using this approach.