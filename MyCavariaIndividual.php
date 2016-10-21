<?php

class MyCavariaIndividual {
  public $id = 0;
  public $hash = '';
  public $firstName = '';
  public $lastName = '';
  public $organizations = array();

  public function __construct($contact_id = NULL) {
    global $user;

    if (!isset($contact_id)) {
      // no explicit contact id is given, get the one of the current drupal user
      $params = array(
        'uf_id' => $user->uid,
        'sequential' => 1,
      );
      $results = civicrm_api3('UFMatch', 'get', $params);
      if ($results['count'] == 0) {
        throw new Exception("U hebt een Drupal login, maar geen overeenkomstig CiviCRM contact.");
      }

      $contact_id = $results['values']['0']['contact_id'];
    }

    // get the contact
    $contact = civicrm_api3('Contact', 'getsingle', array(
      'id' => $contact_id,
      'contact_type' => 'Individual',
    ));

    $this->id = $contact['id'];
    $this->hash = $contact['hash'];
    $this->firstName = $contact['first_name'];
    $this->lastName = $contact['id'];

    $this->getOrganizations();
  }

  private function getOrganizations() {
    $allowedRelationships = array(
      15, // bestuurslid bij
      17, // ondervoorzitter bij
      16, // penningmeester bij
      14, // secretaris bij
      13, // voorzitter
      12, // contactpersoon cavaria bij
    );

    // get the relationships for this contact
    $relationships = civicrm_api3('Relationship', 'get', array(
      'contact_id_a' => $this->id,
      'is_active' => 1,
      'sequentional' => 1,
    ));

    foreach ($relationships['values'] as $relationship) {
      // check if the rel. type id is one that matters in this case
      if (in_array($relationship['relationship_type_id'], $allowedRelationships)) {
        // make sure the organizations is not in the array yet
        if (!array_key_exists($relationship['contact_id_b'], $this->organizations)) {
          $this->organizations[$relationship['contact_id_b']] = new MyCavariaOrganization($relationship['contact_id_b']);
        }
      }
    }

  }
}