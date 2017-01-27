<?php

/**
 * @file
 * Handles the display/submission of the admin settings form for this module.
 */

/**
 * Defines the admin settings form.
 *
 * @param array $form
 *   The Drupal form definition.
 * @param array $form_state
 *   The Drupal form state.
 *
 * @return array
 *   The Drupal form definition.
 */
function islandora_sundog_admin_form(array $form, array &$form_state) {
  $form['islandora_sundog_sample_warning'] = array(
    '#markup' => 'Note: this user interface for managing custom Solr fields with Sundog is intended to illustrate how the module works. We will need to create a more flexible UI to make this module useful.'
  );
  $form['islandora_sundog_object_label_field'] = array(
    '#title' => t('Solr field label for the object title'),
    '#type' => 'textfield',
    '#size' => 60,
    '#default_value' => variable_get('islandora_sundog_object_label_field', 'mycustomlabelfieldname'),
    '#description' => t("The label you want to assign to the custom Solr field containing the object's label/title. The value of the field will be converted to all upper case."),
    '#maxlength' => 255,
  );
  $form['islandora_sundog_object_namespace_field'] = array(
    '#title' => t('Solr field label for the object PID namespace'),
    '#type' => 'textfield',
    '#size' => 60,
    '#default_value' => variable_get('islandora_sundog_object_namespace_field', 'mycustomnamespacefieldname'),
    '#description' => t("The label you want to assign to the custom Solr field containing the object's PID namespace."),
    '#maxlength' => 255,
  );


  return system_settings_form($form);
}
