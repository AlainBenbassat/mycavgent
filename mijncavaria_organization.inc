<?php

function mijncavaria_organization_form() {
  civicrm_initialize();

  $form = array();

  try {
    // get query string parameters
    $queryString = drupal_get_query_parameters();


    // make sure we have an id and a hash (values a and b)
    if (array_key_exists('a', $queryString) && array_key_exists('b', $queryString)) {
      // get the organization
      $organization = new MyCavariaOrganization($queryString['a']);

      // make sure the hash corresponds
      if ($organization->hash != $queryString['b']) {
        throw new Exception("Kan de organisatie niet vinden. Foutcode = 2.", 999);
      }
    }
    else {
      throw new Exception("Geen organisatie opgegeven.");
    }
  }
  catch (Exception $e) {
    $formattedError = '<p>' . $e->getMessage() . '</p>';
    $formattedError .= '<p><a href="' . url('mijncavaria') . '">Terug naar overzicht</a></p>';
    $form['error'] = array(
      '#markup' => $formattedError,
    );
    return $form;
  }

  $form['a'] = array(
    '#type' => 'hidden',
    '#value' => $organization->id,
  );

  $form['b'] = array(
    '#type' => 'hidden',
    '#value' => $organization->hash,
  );

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => 'Naam organisatie',
    '#default_value' => $organization->name,
    '#description' => 'De naam van de organisatie kan u zelf niet wijzigen. Neem contact op met Cavaria om dit te doen.',
    '#attributes' => array(
      'class' => array('readonly-input'),
      'readonly' => 'readonly',
    ),
    '#prefix' => '<h2>Wijzig organisatie</h2>',
  );

  $form['street'] = array(
    '#type' => 'textfield',
    '#title' => 'Straat',
    '#default_value' => $organization->street,
  );

  $form['addressLine1'] = array(
    '#type' => 'textfield',
    '#title' => 'Extra adresregel 1',
    '#default_value' => $organization->addressLine1,
  );

  $form['addressLine2'] = array(
    '#type' => 'textfield',
    '#title' => 'Extra adresregel 2',
    '#default_value' => $organization->addressLine2,
  );

  $form['postalCode'] = array(
    '#type' => 'textfield',
    '#title' => 'Postcode',
    '#default_value' => $organization->postalCode,
  );

  $form['city'] = array(
    '#type' => 'textfield',
    '#title' => 'Gemeente',
    '#default_value' => $organization->city,
  );

  $form['submit'] = array(
    '#type'=> 'submit',
    '#value'=> 'Opslaan',
  );

  $form['cancel'] = array(
    '#markup' => '<a href="' . url('mijncavaria') . '">annuleren</a>',
  );

  return $form;
}

function mijncavaria_organization_form_submit($form, &$form_state) {
  try {
    // get the current contact
    $currentContact = new MyCavariaIndividual();

    // make sure the submitted organization is valid
    if (array_key_exists($form_state['values']['a'], $currentContact->organizations)) {
      // update the org. data
      $currentContact->organizations[$form_state['values']['a']]->update($form_state['values']);
    }
    else {
      throw new Exception('Kan de gegevens de organisatie niet bewaren. Foutcode = 2.');
    }

    $message = 'Gegevens van ' . $form_state['values']['name'] . ' zijn bijgewerkt.';
    $messageType = 'status';
  }
  catch (Exception $e) {
    $message = $e->getMessage();
    $messageType = 'error';
  }

  drupal_set_message($message, $messageType);
  $form_state['redirect'] = 'mijncavaria';
}